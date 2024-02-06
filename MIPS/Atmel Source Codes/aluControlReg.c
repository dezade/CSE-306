#include<avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(){

    DDRB = 0x00; // higher 8 bits 
    DDRA = 0x00; // lower 8 bits
    DDRD = 0b10000001; // 0 flag -> D0, clkout -> D7, D1 -> clkin,   
	PORTD = 0x00;
    // 0-4 normal
    // 5 zero 
    // 6 sp
    unsigned char reg[7]= {0x00,0x00,0x00,0x00,0x00,0x00,0xFF};


    // int inp[16]; 
    // for(int i =0 ; i < 16; ++i) inp[i] = 1; 

    // int mask = 0;  
    // for(int i = 0 ; i < 4; ++i )
    // {
    //     mask |= (inp[i]<<i);
    // } 

    while(1){
        while( PIND1 == 0 );
        _delay_ms(2);
        int maskh = PINB;
		int maskl = PINA;  
        int opcode = maskh; 
		opcode = (opcode >> 4); 


		switch(opcode){
			case 0 : 
			{
				// sub 
				reg[(maskl & (0x0F))] = reg[((maskl & 0xF0)>>4)] - reg[(maskh & 0x0F)];
				break; 
			}
			case 1: 
			{
				// sw

				break; 
			}
			case 2 : 
			{
				// sll
				reg[((maskl & 0xF0)>>4)] = reg[(maskh & 0x0F)] << (maskl & 0x0F);
				break; 
			}
			case 3 : 
			{
				// srl
				reg[((maskl & 0xF0)>>4)] = reg[(maskh & 0x0F)] >> (maskl & 0x0F);
				break;
			}
			case 4 : 
			{
				// lw
				break; 
			}
			case 5 : 
			{
				// ori
				reg[((maskl & 0xF0)>>4)] = reg[(maskh & 0x0F)] | (maskl & 0x0F);
				break; 
			}
			case 6 : 
			{
				// bneq  
				if( reg[(maskh & 0x0F)] - reg[((maskl & 0xF0)>>4)] != 0 ){
					///do something. send 0 flag
				}
				break; 
			}
			case 7 : 
			{
				// AND
				reg[(maskl & (0x0F))] = reg[((maskl & 0xF0)>>4)] & reg[(maskh & 0x0F)];
				break; 
			}
			case 8 : 
			{
				// addi
				reg[((maskl & 0xF0)>>4)] = reg[(maskh & 0x0F)] + (maskl & 0x0F);
				break; 
			}
			case 9 : 
			{
				// NOR
				reg[(maskl & (0x0F))] = ~(reg[((maskl & 0xF0)>>4)] | reg[(maskh & 0x0F)]);
				break; 
			}
			case 10 : 
			{
				// andi
				reg[((maskl & 0xF0)>>4)] = reg[(maskh & 0x0F)] & (maskl & 0x0F);
				break;  
			}
			case 11: 
			{
				// OR
				reg[(maskl & (0x0F))] = reg[((maskl & 0xF0)>>4)] | reg[(maskh & 0x0F)];
				break;  
			}
			case 12 : 
			{
				// subi
				reg[((maskl & 0xF0)>>4)] = reg[(maskh & 0x0F)] - (maskl & 0x0F);
				break; 
			}
			case 13 : 
			{
				// beq  
				if( reg[(maskh & 0x0F)] - reg[((maskl & 0xF0)>>4)] == 0 ){
					///do something. send 0 flag
				}
				break; 
			}
			case 14 : 
			{
				// add
				reg[(maskl & (0x0F))] = reg[((maskl & 0xF0)>>4)] + reg[(maskh & 0x0F)];
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