#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <ctype.h>
#include "lcd.h"

#define BAUD 115200
#define MYUBRR F_CPU/16/BAUD-1
#define ARRAYSIZE 14
char received;
int arrayPos = 0;

void USART_Init( unsigned int ubrr );
void USART_Transmit( unsigned char data );
char USART_Receive( void );
void wait (int ms);

int main( void )
{
	// Init I/O
	DDRD = 0xF8;			// PORTD(7) output, PORTD(6:0) input
	// Init LCD
	init_4bits_mode();
	
	//char str[ARRAYSIZE] = "kadir";
	//int strLenght = ARRAYSIZE;
	//int i = 0;
	
	DDRD = 0b11111111;
	
	USART_Init ( MYUBRR );
	//USART_Transmit('S' );
	PORTD= 0xFF;
	wait(1000);
	PORTD = 0x00;
	lcd_write_command(0x01);
	lcd_write_command(0x02);
	while(1)
	{
		//USART_Transmit( str[i] );
		//i++;
		//if(i >= strLenght)
		//	i = 0;
		USART_Receive();
		if(received >= 97 && received <=122)
			received = received - 32;
		if(toupper(received)=='Z')
		{
			lcd_write_command(0x01);
			lcd_write_command(0x02);
			arrayPos = 0;
		}
		else if(received<32 || received > 125 || received == 127)
		{
		}
		else
		{
			if(arrayPos == ARRAYSIZE)
			{
				lcd_write_command(0x01);
				lcd_write_command(0x02);
				arrayPos = 0;
			}
			lcd_write_data(received);//toupper(received));
			arrayPos++;
		}		
	}
	return(0);
}

void USART_Init( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	//UCSR0C = (1<<USBS)|(3<<UCSZ0);
	//7-bit initialization
	UCSR0C = 0b00001100;
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while (!( UCSR0A & (1<<UDRE)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

char USART_Receive( void )
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1<<RXC)));
	/* Get and return received data from buffer */
	received = UDR0;
	return UDR0;
}

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );
	}
}
