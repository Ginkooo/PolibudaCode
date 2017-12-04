#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile char i = 0; // deklaracja zmiennej globalnej, której kompilator nie optymalizuje
                     // "hardkodując" jej w binarce

ISR(TIMER0_OVF_vect) { // definicja procedury przerwanie
	++i;
	if (i>99) {
		i = 0;
		PORTA ^= 255;
        // jeśli ilość wywołań przerwania dobiłą 100, to włacz/wyłącz diody
	}
}

int main() {
    // ustawienie timera

	TCNT0 = 130;
	TIMSK |= (1<<TOIE0);
	TCCR0 = (1<<CS01);


	sei(); // włączenie obsługi przerwań
	DDRA = 255;
	while (1) {}
}
