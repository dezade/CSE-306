#include<avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(){
  
  MCUCSR|=(1<<JTD);
  MCUCSR|=(1<<JTD);

  DDRB = 0x00; // higher 8 bits
  DDRA = 0x00; // lower 8 bits
  DDRC = 0xFF; // higher 4 bits -> address, lower 4 bits -> data
  DDRD = 0b11000001; // D0 -> ZF , D7 -> clkout ,D6 -> clkout for ShowregFile, D1 -> clkin,
  PORTD = 0x00;
  // 0-4 normal
  // 5 zero
  // 6 sp
  unsigned char reg[7]= {0x00,0x00,0x00,0x00,0x00,0x00,0x0F};
  unsigned char data[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  
  // int inp[16];
  // for(int i =0 ; i < 16; ++i) inp[i] = 1;

  // int mask = 0;
  // for(int i = 0 ; i < 4; ++i )
  // {
  //     mask |= (inp[i]<<i);
  // }

  while(1){
    while(!(PIND & 0x02));
    _delay_ms(2);
    unsigned char maskh = PINB;
    unsigned char maskl = PINA;
    unsigned char opcode = maskh;
    opcode = (opcode >> 4);


    switch(opcode){
      case 0 :
      {
        // sub
        reg[(maskl & (0x0F))] = reg[((maskl & 0xF0)>>4)] - reg[(maskh & 0x0F)];
        PORTC = ((maskl & (0x0F)) << 4) | reg[(maskl & (0x0F))]; 
        PORTD = 0x40;
        _delay_ms(1);
        PORTD = 0x00;
        break;
      }
      case 1:
      {
        // sw $t3, 5($t4) 
        
        unsigned char src = maskh&0x0F;  //t4
        unsigned char dest = maskl>>4;   //t3
        unsigned char offset = maskl & 0x0F;
        
        data[reg[src]+offset] = reg[dest];
        
        PORTC = ((maskl>>4)) | reg[(maskl>>4)];
        PORTD = 0x40;
        _delay_ms(1);
        PORTD = 0x00;

        break;
      }
      case 2 :
      {
        // sll
        reg[((maskl & 0xF0)>>4)] = reg[(maskh & 0x0F)] << (maskl & 0x0F);
        PORTC = ((maskl & 0xF0)) | reg[((maskl & 0xF0)>>4)];
        PORTD = 0x40;
        _delay_ms(1);
        PORTD = 0x00;
        break;
      }
      case 3 :
      {
        // srl
        reg[((maskl & 0xF0)>>4)] = reg[(maskh & 0x0F)] >> (maskl & 0x0F);
        PORTC = ((maskl & 0xF0)) | reg[((maskl & 0xF0)>>4)];
        PORTD = 0x40;
        _delay_ms(1);
        PORTD = 0x00;
        break;
      }
      case 4 :
      {
        // lw $t3, 5($t4)
        unsigned char src = maskh&0x0F;  //t4
        unsigned char dest = maskl>>4;   //t3
        unsigned char offset = maskl & 0x0F;
        
        reg[dest]=data[reg[src]+offset] ;
        
        PORTC = ((maskl>>4)) | reg[(maskl>>4)];
        PORTD = 0x40;
        _delay_ms(1);
        PORTD = 0x00;
		

        break;
      }
      case 5 :
      {
        // ori
        reg[((maskl & 0xF0)>>4)] = reg[(maskh & 0x0F)] | (maskl & 0x0F);
        PORTC = ((maskl & 0xF0)) | reg[((maskl & 0xF0)>>4)];
        PORTD = 0x40;
        _delay_ms(1);
        PORTD = 0x00;
        break;
      }
      case 6 :
      {
        // bneq
        if( reg[(maskh & 0x0F)] - reg[((maskl & 0xF0)>>4)] != 0 ){
          ///do something. send 0 flag
          
          PORTD = 0x00;
        }
        break;
      }
      case 7 :
      {
        // AND
        reg[(maskl & (0x0F))] = reg[((maskl & 0xF0)>>4)] & reg[(maskh & 0x0F)];
        PORTC = ((maskl & (0x0F)) << 4) | reg[(maskl & (0x0F))];
        PORTD = 0x40;
        _delay_ms(1);
        PORTD = 0x00;
        break;
      }
      case 8 :
      {
        // addi
        reg[((maskl & 0xF0)>>4)] = reg[(maskh & 0x0F)] + (maskl & 0x0F);
        PORTC = ((maskl & 0xF0)) | reg[((maskl & 0xF0)>>4)];
        PORTD = 0x40;
        _delay_ms(1);
        PORTD = 0x00;
        break;
      }
      case 9 :
      {
        // NOR
        reg[(maskl & (0x0F))] = ~(reg[((maskl & 0xF0)>>4)] | reg[(maskh & 0x0F)]);
        PORTC = ((maskl & (0x0F)) << 4) | reg[(maskl & (0x0F))];
        PORTD = 0x40;
        _delay_ms(1);
        PORTD = 0x00;
        break;
      }
      case 10 :
      {
        // andi
        reg[((maskl & 0xF0)>>4)] = reg[(maskh & 0x0F)] & (maskl & 0x0F);
        PORTC = ((maskl & 0xF0)) | reg[((maskl & 0xF0)>>4)];
        PORTD = 0x40;
        _delay_ms(1);
        PORTD = 0x00;
        break;
      }
      case 11:
      {
        // OR
        reg[(maskl & (0x0F))] = reg[((maskl & 0xF0)>>4)] | reg[(maskh & 0x0F)];
        PORTC = ((maskl & (0x0F)) << 4) | reg[(maskl & (0x0F))];
        PORTD = 0x40;
        _delay_ms(1);
        PORTD = 0x00;
        break;
      }
      case 12 :
      {
        // subi
        reg[((maskl & 0xF0)>>4)] = reg[(maskh & 0x0F)] - (maskl & 0x0F);
        PORTC = ((maskl & 0xF0)) | reg[((maskl & 0xF0)>>4)];
        PORTD = 0x40;
        _delay_ms(1);
        PORTD = 0x00;
        break;
      }
      case 13 :
      {
        // beq
        if( reg[(maskh & 0x0F)] - reg[((maskl & 0xF0)>>4)] == 0 ){
          ///do something. send 0 flag
          PORTD = 0x01;
          
        }
        break;
      }
      case 14 :
      {
        // add
        reg[(maskl & (0x0F))] = reg[((maskl & 0xF0)>>4)] + reg[(maskh & 0x0F)];
        PORTC = ((maskl & (0x0F)) << 4) | reg[(maskl & (0x0F))];
        PORTD = 0x40;
        _delay_ms(1);
        PORTD = 0x00;
        break;
      }
      case 15 :
      {
        // Jump. Do nothing
        break;
      }
      default :
      {
        break;
      }
    }
    PORTD = 0b10000000;
    _delay_ms(2);
    PORTD = 0x00;
  }
}