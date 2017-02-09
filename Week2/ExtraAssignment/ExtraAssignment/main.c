/*
 * ExtraAssignment.c
 *
 * Created: 9/2/2017 1:01:37 PM
 * Author : Kadir Seker and Christian Paans
 * 
 * In this assignment, we put our control of the 7 segment display 
 * to the test. Using 2 segment displays, we made a small calculator
 * that can use 2 input integers and can calculate the result of any
 * of the 4 basic operations ( + - x / ).
 *
 * result = valueA OPERATOR valueB
 * 
 * PC2 = valueA++
 * PC3 = valueA--
 * PC0 = valueB++
 * PC1 = valueB--
 * PD0 = /
 * PD1 = x
 * PD2 = -
 * PD4 = +
 * PD5 = Clear result display and return to the view of the integers.
 * An image of the setup is provided in the repository.
 * The video(Dutch audio) of this setup in action can be seen on:
 * ---pending---
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
	0b01111111, 0b01101111, 0b01111001};

void displayA(int digit, int dot)
{
	if(digit>9 || digit < 0)
		PORTA = lookuptable[11];
	else
		PORTA = lookuptable[digit];
	if(dot)
		PORTA = (PORTA + 0x80);
}
void displayB(int digit)
{
	if(digit>9 || digit < 0)
		PORTB = lookuptable[11];
	else
		PORTB = lookuptable[digit];
}

int main( void )
{
	// Init I/O
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0x00;
	DDRD = 0x00;
	int valueA = 0;
	int valueB = 0;
	int calculated = 0;
	double result = 0;

	while (1)
	{
		if(PINC & 1)
		{
			if (valueB < 9)
			{
				valueB++;
			}
		}
		else if(PINC & 2)
		{
			if (valueB > 0)
			{
				valueB--;
			}
		}
		else if(PINC & 4)
		{
			if (valueA < 10)
			{
				valueA++;
			}
		}
		else if(PINC & 8)
		{
			if (valueA > 0)
			{
				valueA--;
			}
		}
		if (PIND & 1 && !calculated)
		{
			result = (valueA*1.0)/(valueB*1.0);
			calculated = 1;
		} 
		else if(PIND & 2 && !calculated)
		{
			result = valueA*valueB;
			calculated = 1;
		}
		else if (PIND & 4 && !calculated)
		{
			result = valueA - valueB;
			calculated = 1;
		}
		else if (PIND & 16 && !calculated)
		{
			result = valueA + valueB;
			calculated = 1;
		}
		if (PIND & 32)
		{
			calculated = 0;
		}
		if (calculated)
		{
			if (result>0 && result <10 && ((int)(result*10)%10)>0)
			{
				displayA((int)(result),1);
				displayB(((int)(result*10))%10);
			}
			else if (result>=10)
			{
				displayA(result/10,0);
				displayB(((int)result)%10);
			}
			else if (result < 0)
			{
				PORTA = 0b01000000;
				displayB(result*-1);
			}
			else
			{
				PORTA = 0b00000000;
				displayB(result);
			}
		}
		else
		{
			displayA(valueA,0);
			displayB(valueB);
		}
		wait(500);
	}
	return 1;
}