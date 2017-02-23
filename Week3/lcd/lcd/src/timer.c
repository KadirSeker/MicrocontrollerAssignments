/*
 * timer.c
 *
 * Created: 16-2-2017 13:01:39
 *  Author: Christiaan
 */ 

 #define F_CPU 8000000

 #include <string.h>
 #include <timer.h>
 #include <avr/io.h>
 #include <util/delay.h>
 #include <avr/interrupt.h>
 #include <lcd.h>

int counter = 0;

 void timer2init(void)
 {
	TIMSK |= (1<<TOIE2);
	sei();
	TCNT2 = 0xFF;
	TCCR2 = 0b00011111;
 }

 ISR(TIMER2_OVF_vect)
 {
	TCNT2 = 0xFF;
	counter++;
 }