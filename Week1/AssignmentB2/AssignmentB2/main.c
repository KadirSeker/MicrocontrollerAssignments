/*
 * AssignmentB2.c
 *
 * Created: 2/4/2017 10:15:33 AM
 * Author : Kadir Seker, Cas Koopmans and Berend Vet
 */

 #include <avr/io.h>
 #define F_CPU 8000000
 #include <util/delay.h>

 void wait( int ms )
{
for (int i=0; i<ms; i++)
	{
		 _delay_ms( 1 );
	}
}

int main(void)
{
	DDRD = 0b11111111;			// All pins PORTD are set to output

	while (1)
	{
		PORTD = 0x80;
		wait(500);
		PORTD = 0x0;
		wait(500);
	}
	return 1;
}