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

	DDRC = 0b11111111;
	DDRD = 0b00000000;
	timer2initB3();
	sei();
	while(1)
	{
		
	}

	return 1;
}