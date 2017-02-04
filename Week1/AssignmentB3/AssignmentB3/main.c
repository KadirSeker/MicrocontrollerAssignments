/*
 * AssignmentB3.c
 *
 * Created: 2/2/2017 1:01:37 PM
 * Author : Kadir Seker, Cas Koopmans and Berend Vet
 */ 

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );
	}
}

int main(void)
{
	DDRD = 0b11111111;			// All pins PORTD are set to output
	DDRC = 0b00000000;			// All pins PORTC are set to input
	
	while (1)
	{
		if(PINC & 1)
		{
			PORTD = 0x80;
			wait(500);
			PORTD = 0x0;
			wait(500);
		}
	}
	return 1;
}

