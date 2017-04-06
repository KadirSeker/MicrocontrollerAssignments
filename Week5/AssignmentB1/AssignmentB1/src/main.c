/* AssignmentB1.c
 * Author : Kadir Seker
 */ 
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

void wait( int ms );
void adcInit(void);

int main( void )
{
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRA = 0xFF;				// set PORTA for output
	DDRB = 0xFF;				// set PORTB for output
	adcInit();

	while (1)
	{
		PORTA = ADCH;
		PORTB = ADCL;
		wait(100);
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
	ADMUX = 0b01100001;		// AREF = VCC, left adjusted, pin PF1 channel 1
	ADCSRA = 0b11100110;	// ADC-enable, no interrupts, free running, divided by 64
}