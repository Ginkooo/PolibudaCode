#include <avr/io.h> //Library with all IO functions
#include <util/delay.h> //deelay function
unsigned char h;

int main() {
	DDRA = 0xFF; //Set all PORTA pins to output mode, they are in input mode by default.
	while(1) {
		PORTA ^= 0xFF; //Set data transfer on and off
		_delay_ms(500); //Set delay to see anything
	}
}
