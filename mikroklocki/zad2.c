#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile char i = 0;
volatile char curr_delay;

void reset_timer(char n) {
    // funkcja resetuje timer, który zaczyna liczyć od n
	TCNT0 = n;
}

ISR(TIMER0_OVF_vect) {
    // Zapala diody, które sygnalizują, że watchdog zadziałał
	PORTA = curr_delay;
}

int main() {
	char n = 192; //Od tej wartości liczymy, by mieć przerwanie co 4 ms
	TIMSK |= (1<<TOIE0);
	TCCR0 = (1<<CS01) | (1<<CS00);
	sei();
	DDRA = 255;
	while (1) {
		reset_timer(n);
		curr_delay = 1; // jeśli watchdog by zadziałał teraz, to zapalamy diodę 0
		_delay_ms(3); // symulujemy działanie, trwające odpowiednią ilość czasu
		curr_delay = 128; // zapalona zostałaby dioda 7
		reset_timer(n);
		_delay_ms(5); // symulujemy działanie, które trwa dłużej niż powinno
	}
}
