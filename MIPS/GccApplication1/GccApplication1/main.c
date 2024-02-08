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
  DDRD = 0b01000000; // D7 -> clkin D6 ->clkout D5 -> feedback D0 -> ZF
  PORTD = 0x00;
  DDRA = 0xFF; //lower 8 bit output
  DDRB = 0xFF; // higher 8 bit output
  
  DDRC = 0xFF; 

  unsigned int instruction[] = {0x850A, 0x8517, 0x0012, 0x8503, 0xD202, 0x8531, 0xF080, 0x8530, 0x2333, 0x3333, 0x1432, 0x4431, 0xB030, 0x1600, 0xC661, 0x8661, 0x4610};
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
      counter = jump_address;
    }
    else if(opcode == 0x000D) //beq check
    {  
      //while(!(PIND & 0x20));
      if (PIND & 0x01) counter += offset_address;
      
    }
    else if(opcode == 0x0006) //bneq check
    {
      while(!(PIND & 0x20));
      if (!(PIND & 0x01)) counter += offset_address;
    }  
    
    PORTD = 0x40; // sending clk
    _delay_ms(2);
    PORTD = 0x00;
    
  }
  
  //0x0F;
  //PORTD = 0xf0;

  }