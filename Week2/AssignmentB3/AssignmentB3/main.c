/*
 * AssignmentB3.c
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

int lookuptable[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 
	0b01111111, 0b01101111, 0b01110111, 0b01111100, 0b00111001, 0b01011110, 0b01111011, 0b01110001, 0b01111001};

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
	int value = 6;

	while (1)
	{
		if((PINC & 1) && (PINC & 2))
		{
			value = 0;
		}
		else if(PINC & 2)
		{
			value++;
			if(value > 16)
			{
				value = 16;
			}
		}
		else if(PINC & 1)
		{
			value--;
			if(value < -1)
			{
				value = -1;
			}
		}
		display(value);
		wait(500);
	}
	return 1;
}