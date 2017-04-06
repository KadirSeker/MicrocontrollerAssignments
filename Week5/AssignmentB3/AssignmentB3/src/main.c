/* AssignmentB3.c
 * Author : Kadir Seker
 */
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"

void wait( int ms );
void adcInit(void);

int main( void )
{
	DDRF = 0x00;
	DDRA = 0xFF;
	
	adcInit();
	
	init_lcd_4bit();
	wait(300);
	char tempToDisplay[15];
	clearScreen();

	while (1)
	{
		clearScreen();
		int i = ADCH;
		sprintf(tempToDisplay, "%i°C", i);
		wait(5);
		
		display_text(tempToDisplay);
		wait(5);
		memset(tempToDisplay, 0, 15);
		PORTA = ADCH;
		wait(2000);
	}
}

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void adcInit()
{
	ADMUX =  0b11100001;
	ADCSRA = 0b11100110;
}