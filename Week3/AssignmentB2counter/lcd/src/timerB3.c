/*
 * timerB3.c
 *
 * Created: 23-2-2017 11:09:26
 *  Author: Christiaan
 */ 
  #define F_CPU 8000000

  #include <string.h>
  #include <timerB3.h>
  #include <avr/io.h>
  #include <util/delay.h>
  #include <avr/interrupt.h>

  #define COMPVALUE1 117
  #define COMPVALUE2 195

  void timer2initB3()
  {
	  TIMSK |= (1<<TOIE2);
	  TCNT2 = 0;
	  TCCR2 = 0b00011101;
	  OCR2 = COMPVALUE1;
  }

  ISR(TIMER2_COMP_vect)
  {
	  if(OCR2 == COMPVALUE1)
	  {
		OCR2 = COMPVALUE2;
		PORTD = 0b10000000;
	  } 
	  else if(OCR2 == COMPVALUE2)
	  {
		OCR2 = COMPVALUE1;
		PORTD = 0b00000000;
	  }
  }