#include <avr/io.h>
#include <avr/delay.h>


int main() {
	DDRA = 0xFF;
	DDRB = 0xF0;
	TCCR0 |= (1<<CS02) | (1<<CS01);
	while (1) {PORTA = TCNT0;}
}
