/*
 * rough.c
 *
 * Created: 2/7/2024 1:17:53 PM
 * Author : RAFTEL
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>



volatile unsigned char p0 = 0x03;
/*
int main(void)
{
	DDRB = 0xFF; 
	
	
	while(1){
		int i = 0;
		while(i < 100){
			++i; 
			PORTB = 0x03;
			_delay_ms(10); 
		}
		i = 0; 
		while(i < 100)
		{
			PORTB = 0x01;
			_delay_ms(10); 
			++i ;
		}
	}
}
*/

int main(void)
{
    DDRB = 0x03;
	while(1)
	{	
		while(!(PINB & 0x80)) PORTB = 0x00;
		_delay_ms(100);
		if((PINB & 0x40) ) 
		{	

			while( !(PINB & 0x80))PORTB = p0;
			_delay_ms(100);
			PORTB = 0x00;
		}
		else if (PINB & 0x20)
		{
			DDRB = 0x00;
			while(!(PINB & 0x80));
			
			p0 = 0x03 & PINB;
			DDRB = 0x03;
			_delay_ms(100);
			/*
			DDRB = 0x03;
			PORTB = p0;
			while(PINB7 != 1) PORTB = p0;
			_delay_ms(100);
			*/
		}
	}
}

