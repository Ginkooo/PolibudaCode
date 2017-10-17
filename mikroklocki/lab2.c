#include <avr/io.h>
#include <util/delay.h>

void ex1() {
	DDRA = 0xff;
	DDRB = 0xff;
	
	char chars[4] = {
					 0b01100001,
					 0b11000101,
					 0b11110101,
					 0b00111001
					 };

	char places[4] = {
				   	 0b11110001,
				     0b11110010,
				     0b11110100,
				     0b11111000
					};
	
	int i;
	for(;;) {
		for(i=0; i<4; i++) {
			PORTA = chars[i];
			PORTB = ~places[i];
			_delay_ms(2);
		}
	}
}

void ex2() {
	DDRA = 0xff;
	DDRB = 0xff;

	char digits[10] = { 
				   0b00000011,
				   0b10011111,
				   0b00100101,
				   0b00001101,
				   0b10011001,
				   0b01001001,
				   0b01000001,
				   0b00011111,
				   0b00000001,
				   0b00001001
				  };

	int i;
	int j;
	for(;;) {
		for(i=0; i<=95; i+=5) {
			int first = i % 10;
			int second = i / 10;

			for(j=0; i<250; j++)
			{
				PORTA = digits[first];
				PORTB = 0b111110111;
				_delay_ms(2);
				PORTA = digits[second];
				PORTB = 0b111111011;
				_delay_ms(2);
			}
		}
	}

}

int main() {
	DDRA = 0;
	DDRB = 0;
	ex2();
	DDRA = 0;
	DDRB = 0;
}
