/*
 * AssignmentB4.c
 * Run the example code provided by the teacher.
 *
 * Created: 9/2/2017 1:01:37 PM
 * Author : Kadir Seker, Christian Paans and Berend Vet
 */

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR( INT1_vect )
{
	if(PORTC & 1)
		PORTC = 128;
	else
		PORTC = PORTC/2;		
}

ISR( INT2_vect )
{
	if(PORTC & 128)
		PORTC = 1;
	else
		PORTC = PORTC*2;
}

int lookuptable[] = {0b01100001, 0b01100100, 0b01001100, 0b00011100, 0b01011000, 0b01010010, 0b01000011, 0b00100011};

void display(int digit)
{
	if(digit>15 || digit < 0)
		PORTB = lookuptable[16];
	else
		PORTB = lookuptable[digit];
}

int main( void )
{
	// Init I/O
	DDRB = 0xFF;
	DDRC = 0x00;
	int value = 0;
	int waitduration = 500;

	// Init Interrupt hardware
	EICRA |= 0x2C;			// INT2 falling edge, INT1 rising edge
	EIMSK |= 0x06;			// Enable INT2 & INT1
	sei();				

	while (1)
	{
		display(value);
		wait(waitduration);
		value++;
		if(value > 7)
		{
			value = 0;
		}
		if ( (PINC&2) && (PINC&1) )
		{
			waitduration = 500;
		}
		else if(PINC & 2)
		{
			if(waitduration > 100)
				waitduration = waitduration - 100;
		}
		else if(PINC & 1)
		{
			if(waitduration<1000)
				waitduration = waitduration + 100;
		}
	}

	return 1;
}