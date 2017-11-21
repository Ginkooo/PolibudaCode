#include <avr/io.h>
#include <avr/delay.h>

void delay() {
	for(char i=0; i<10; ++i ) {
		TCNT0 = 155;
		TCCR0 |= (1<<CS00) | (1<<CS02);
		while (!(TIFR & 1)) {}
		TCCR0 &= ~((1<<CS00) | (1<<CS02));
		TIFR |= 1;
	}
}

int main() {
	DDRB = 0x01;
	PORTB = 0;
	while(1) {
		delay();
		PORTB ^= 1;
	}
}
