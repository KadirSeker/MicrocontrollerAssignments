/*
 * AssignmentB6.c
 *
 * Created: 2/3/2017 2:26:13 PM
 * Author : Kadir Seker, Cas Koopmans and Berend Vet
 */ 

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

int changed = 0;			// Tracks the status of whether or not the frequency has been changed
int freq = 1;				// Blinking frequency

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
			if(changed == 0 && freq == 1)
			{
				changed = 1;
				freq = 4;
			}
			else if (changed == 0 && freq == 4)
			{
				changed = 1;
				freq = 1;
			}
		}
		else
		{
			changed = 0;				
		}
		PORTD = 0x80;
		wait(500/freq);
		PORTD = 0x0;
		wait(500/freq);
	}
	return 1;
}

