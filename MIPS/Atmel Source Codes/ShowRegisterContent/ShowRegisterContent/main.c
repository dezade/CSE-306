#define F_CPU 1000000

#include<avr/io.h>
#include <util/delay.h>

int main(){
	
	MCUCSR|=(1<<JTD);
	MCUCSR|=(1<<JTD);

	DDRA = 0x00; // Scan queried register address (A2-A0)
	DDRB = 0x0F; // Send address to big boss (B3-B0)
	DDRC = 0x00; // Receive data from big boss (C3-C0)
	DDRD = 0xFF; // Show register address (D7-D4) and data (D3-D0)
	
	unsigned char address;
	unsigned char data;

	while(1){
		address = PINA & 0x07;			// Scan queried register address
		PORTB = address;				// Send address to big boss
		_delay_ms(1);					// Wait a moment
		data = PINC & 0x0F;				// Receive data from big boss
		PORTD = (address << 4) | data;	// Show register address and data
	}
}