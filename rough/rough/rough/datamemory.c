/*
 * Experiment1.c
 *
 * Created: 1/21/2024 5:07:26 AM
 * Author : jarin
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 1000000

volatile unsigned int counter;

int main(void)
{
	MCUCSR|=(1<<JTD);
	MCUCSR|=(1<<JTD);
	
	unsigned char data[16];
	int input;
	int Data;
	int output;
	
	DDRA = 0x00; //lower 4 bit input address , upper 4 bit data
	DDRB = 0b00011111; // lower 4 bit output, B7 is clk-in, B6 read in, B5 write in, B4 clk-out
	PORTB = 0x00;
	
	while(1)
	{
		while(!(PINB & 0x80));
		_delay_ms(2);
		if (PINB & 0b01000000) {	//read
			PORTB = 0x0F & (data[PINA & 0x0F]);	
		}
		else if (PINB & 0b00100000) {	//write
			unsigned char in = PINA;
			data[in & 0x0F] = in >> 4;
		}
		PORTB = 0x10;
		_delay_ms(2);
		PORTB = 0x00;		
	}
}
