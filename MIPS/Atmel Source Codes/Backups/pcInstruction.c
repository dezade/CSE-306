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
	
	
	DDRD = 0b01000000; // input of PUSH and ZF
	PORTD = 0x00; // D7 - clkin , D6 - clkout
	//PORTC = 0xFF;
	DDRA = 0xFF; //lower 8 bit output
	DDRB = 0xFF; // higher 8 bit output
	
	unsigned int instruction[20];
	int clock, ZF;
	
	counter = 0;
	
	while(counter<instruction.length)
	{
		while(clock==0);
		_delay_ms(20);
		unsigned int output = instruction[counter];
		
		PORTA = output & 0x00FF;
		PORTB = (output & 0xFF00)>>8;
		
		unsigned int opcode = (output & 0xF000)>>12;
		unsigned int jump_address = (output& 0x0FF0)>>4;
		unsigned int offset_address = (output& 0x000F);
		
		counter++;
		
		_delay_ms(1);
		
		ZF = PIND0;
		clock = PIND7;
		
		if(opcode == 0x000F) // jump check
		{	
			counter = jump_address;
		}
		else if(opcode == 0x000D && ZF==1) //beq check
		{
			counter += offset_address;
			
		}
		else if(opcode == 0x0006 && ZF==0 ) //bneq check
		{
			counter += offset_address;
		}	
		
		PORTD = 0x40;
		_delay_ms(2);
		PORTD = 0x00;
		
	}
	
	//0x0F;
	//PORTD = 0xf0;
}
