#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <lcd.h>
#include <timer.h>
#include <stdlib.h>
#include <stdio.h>
#include <timerB3.h>

int main ( void )
{
	init_4bits_mode();
	_delay_ms(2000);
	lcd_write_command(0);
	lcd_write_command(1);
	_delay_ms(20);
	
	timer2init();
	sei();
	while(1)
	{
		char counter = *getCounterValue();
		lcd_assignmentb2((counter&0x0F)+'0');
		set_cursor(0);
		_delay_ms(1000);
	}

	return 1;
}