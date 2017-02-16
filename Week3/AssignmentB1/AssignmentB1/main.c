/*
 * AssignmentB1.c
 *
 * Created: 16-02-2017
 * Author : Kadir Seker and Christian Paans
 */
 #define F_CPU 8000000

#include "lcd.h"
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


int main(void)
{
	// Init I/O
	DDRD = 0xF8;			// PORTD(7) output, PORTD(6:0) input

	// Init LCD
	init_4bits_mode();

	// Write sample string
	lcd_write_string("Kadir Seker");

	// Loop forever
	while (1)
	{
		if(PIND & 4)	//Pressing PD2 moves the cursor left 
		{
			set_cursor(cursorpos-1);
		}
		else if (PIND & 0)	//Pressing PD0 moves the cursor right
		{
			set_cursor(cursorpos+1);
		}
		PORTD ^= (1<<7);	// Toggle PORTD.7
		_delay_ms( 250 );
	}

	return 1;
}

