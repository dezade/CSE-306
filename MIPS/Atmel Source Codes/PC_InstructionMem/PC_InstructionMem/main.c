/*
 * Experiment1.c
 *
 * Created: 1/21/2024 5:07:26 AM
 * Author : jarin
 */ 


#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned int counter;

int main()
{
	MCUCSR|=(1<<JTD);
	MCUCSR|=(1<<JTD);
	
  DDRD = 0b01000000; // D7 -> clkin D6 ->clkout D5 -> feedback D0 -> ZF
  PORTD = 0x00;
  DDRA = 0xFF; //lower 8 bit output
  DDRB = 0xFF; // higher 8 bit output
  
  DDRC = 0xFF; 

  unsigned int instruction[] = {0x8003, 0x8112, 0x8227, 0xE010, 0x1303, 0x4333, 0xD02C, 0x0202, 0x6052, 0x544A, 0xC446, 0x7151, 0xA440, 0xB414, 0x1650, 0xC661, 0x1610, 0xC661, 0x8505, 0x8514, 0x9101, 0x8661, 0x4610, 0x8661, 0x4610, 0x8524, 0x8111, 0xD121, 0xF1A0, 0x850F};
  //unsigned char clock = PIND & 0x80, ZF = PIND & 0x01;
  
  counter = 0;
  
  int length = sizeof(instruction)/sizeof(unsigned int);
  
  while(counter < length)
  {
    //PORTC = 0xFF; 
    //_delay_ms(10);
    while(!(PIND & 0x80));
    _delay_ms(200);
    unsigned int output = instruction[counter];
    
    PORTA = (unsigned char)(output & 0x00FF);
    PORTB = (unsigned char)((output & 0xFF00)>>8);
   
    unsigned int opcode = (output & 0xF000)>>12;
    unsigned int jump_address = (output & 0x0FF0)>>4;
    unsigned int offset_address = (output & 0x000F);
    
    counter++;
    
    if(opcode == 0x000F) // jump check
    {  
		PORTD = 0x40; // sending clk
		_delay_ms(2);
		PORTD = 0x00;
      counter = jump_address;
    }
    else if(opcode == 0x000D) //beq check
    {  /*
		PORTD = 0x40; // sending clk
		_delay_ms(2);
		PORTD = 0x00;
		PORTC = 0x0F;
      while(!(PIND & 0x20));
	  _delay_ms(2);
	  
      if (PIND & 0x01) 
	  {
		  //PORTC = 0xFF;
		  if(offset_address & 0x08)
		  {
			  counter -= (16 - offset_address);			  
		  }
		  else counter += offset_address;
	  }
	  //PORTC = 0x01;
	  */
		unsigned int temp = 0;
		PORTD = 0x40; // sending clk
		_delay_ms(2);
		PORTD = 0x00;
		PORTC = 0x0F;
		while(!(PIND & 0x20)){temp = PIND;}
		_delay_ms(2);
		//if (PIND & 0x01)
		if(temp & 0x01)
		{
			//PORTC = (unsigned char)offset_address;
			PORTC = 0b10101010;
			_delay_ms(2000);
			if(offset_address & 0x08)
			{
				counter -= (16 - offset_address);
			}
			else counter += offset_address;
			
			if (counter >= length || counter < 0) PORTC = 0x02;_delay_ms(2000);
		}
		PORTC = 0x01;
    }
    else if(opcode == 0x0006) //bneq check
    {
		unsigned int temp = 0;
		PORTD = 0x40; // sending clk
		_delay_ms(2);
		PORTD = 0x00;
		PORTC = 0x0F;
      while(!(PIND & 0x20)){temp = PIND;}
      _delay_ms(2);
      //if (!(PIND & 0x01))
      if(!(temp & 0x01))
      {
		  PORTC = (unsigned char)offset_address;
		  _delay_ms(2000);
	      if(offset_address & 0x08)
	      {
		      counter -= (16 - offset_address);
	      }
	      else counter += offset_address;
		  
		  if (counter >= length || counter < 0) PORTC = 0x02;_delay_ms(2000);
      }
	  PORTC = 0x01;
    }  
    else{
		PORTD = 0x40; // sending clk
		_delay_ms(2);
		PORTD = 0x00;
	}
  }
  
  //0x0F;
  //PORTD = 0xf0;

  }