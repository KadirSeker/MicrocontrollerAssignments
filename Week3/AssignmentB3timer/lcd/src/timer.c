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

unsigned char counter = 0;

 char* getCounterValue(void)
 {
	return &counter;
 }

 void timer2init(void)
 {
	TIMSK |= (1<<TOIE2);
	TCNT2 = 0xFF;
	TCCR2 = 0b00000111;
 }

 ISR(TIMER2_OVF_vect)
 {
	TCNT2 = 0xFF;
	counter++;
 }