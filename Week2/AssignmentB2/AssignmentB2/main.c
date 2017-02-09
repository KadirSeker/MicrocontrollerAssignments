/*
 * AssignmentB2.c
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

int main( void )
{
	// Init I/O
	DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input
	DDRC = 0xFF;
	PORTC = 1;

	// Init Interrupt hardware
	EICRA |= 0x2C;			// INT2 falling edge, INT1 rising edge
	EIMSK |= 0x06;			// Enable INT2 & INT1
	sei();				

	while (1)
	{
		//Empty because the assignment requires it. The purpose is
		//to manipulate the lights with the interrupts only.		
	}

	return 1;
}