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

  unsigned int instruction[] = {0x8503, 0x8518, 0xE102, 0x0103, 0xC22A, 0x850F, 0xA009, 0x5005, 0x8511, 0x7101, 0x2112, 0x853A, 0xB131, 0x3142, 0x3441, 0x8538, 0x9341, 0x8500, 0x1010, 0x8122, 0x1022, 0x8227, 0x1025, 0x4042, 0x4045, 0x4040, 0x8504, 0x8512, 0xD015, 0x8534, 0x8520, 0xD032, 0x8529, 0x8221, 0x8221, 0x620E, 0xC222, 0x6214, 0x850F, 0xA00A, 0x8515, 0x8540, 0xC001, 0xD013, 0x8441, 0xF2A0, 0x8540, 0x850A, 0x8512, 0x8528, 0x8537, 0x1600, 0xC661, 0x1610, 0xC661, 0x1620, 0xC661, 0x8661, 0x4600, 0x8661, 0x4620, 0x1630, 0xC661, 0x8661, 0x4600, 0x8661, 0x4630, 0x800F};
  //unsigned char clock = PIND & 0x80, ZF = PIND & 0x01;
  
  counter = 0;
  
  int length = sizeof(instruction)/sizeof(unsigned int);
  
  while(counter < length)
  {
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
    {
		unsigned int temp = 0;
		PORTD = 0x40; // sending clk
		_delay_ms(2);
		PORTD = 0x00;
		while(!(PIND & 0x20)){temp = PIND;}
		_delay_ms(2);
		//if (PIND & 0x01)
		if(temp & 0x01)
		{
			if(offset_address & 0x08)
			{
				counter -= (16 - offset_address);
			}
			else counter += offset_address;
			
			if (counter >= length || counter < 0) PORTC = 0xF0;
		}
    }
    else if(opcode == 0x0006) //bneq check
    {
		unsigned char temp = 0;
		PORTD = 0x40; // sending clk
		_delay_ms(2);
		PORTD = 0x00;
      while(!(PIND & 0x20)){temp = 0x01 & PIND;}
      _delay_ms(2);
      //if (!(PIND & 0x01))
      if(!(temp & 0x01))
      {
	      if(offset_address & 0x08)
	      {
		      counter -= (16 - offset_address);
	      }
	      else counter += offset_address;
		  
		  if (counter >= length || counter < 0) PORTC = 0xF0;
      }
	  else{
		  PORTC = 0x01;
	  }
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