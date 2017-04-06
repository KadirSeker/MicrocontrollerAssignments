/* AssignmentB2.c
 * Kadir Seker
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)	(1 << (x))

void wait( int ms );
void adcInit(void);

int main( void )
{
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRA = 0xFF;				// set PORTA for output
	adcInit();

	while (1)
	{
		ADCSRA |= BIT(6);
		while ( ADCSRA & BIT(6) );
		PORTA = ADCH;
		wait(500);
	}
}

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

//ADC initialization
void adcInit()
{
	ADMUX = 0b11100001;
	ADCSRA = 0b10000110;
}