#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <lcd.h>
#include <timer.h>
#include <stdlib.h>
#include <stdio.h>

int main ( void )
{
	lcd_init();

	lcd_write_cmd(0);
	_delay_ms(20);

	lcd_write_cmd(1);
	_delay_ms(20);
		
	lcd_write_string("0");
	_delay_ms(20);
	
	lcd_strobe_lcd_e();


	//int direction = 1;
	
	//DDRD = 	0b00000000;
	//PORTA = 1;

	timer2init();
	//TCCR1B |= ((1 << CS10 ) | (1 << CS11 )) ; // Set up timer at Fcpu /64
	int oldcounter = 0;
	while(1)
	{
	
		if(oldcounter != counter)
		{
			oldcounter = counter;
			lcd_write_cmd(0);
			lcd_write_cmd(1);
			lcd_write_string((char *)counter);
			_delay_ms(50);
		}
	}

	return 1;
}