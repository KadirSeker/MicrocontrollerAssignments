/*
 * AssignmentB7a.c
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
	DDRD = 0b11111111;				// All pins PORTD are set to output
	DDRC = 0b00000000;				// All pins PORTC are set to input
	
	while(1)
	{
		if((PINC & 0b00000011) == 0b00000011)	//State 1 - If  Button C0 and C1 are
		{										//pressed simultaneously, execute this
			PORTD = 0b11000011;
			wait(500);
			PORTD = 0b00111100;
			wait(500);
		}
		else if(PINC & 0b00000001)	//State 2 - If  Button C0 is pressed, execute this
		{
			PORTD = 0b11111111;
			wait(500);
			PORTD = 0b00000000;
			wait(500);
		}
		else if(PINC & 0b00000010)	//State 3 - If  Button C1 is pressed, execute this
		{
			PORTD = 0b10101010;
			wait(500);
			PORTD = 0b01010101;
			wait(500);
		}
		else						//Default state - If none of the states above is chosen, execute this.
		{
			PORTD = 0b11111111;
			wait(125);
			PORTD = 0b00000000;
			wait(125);
		}
	}
	return 1;
}