#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile char up = 1; // zmienna sygnalizuje czy dioda powinna być gaszona czy rozświetlana

volatile char counter = 0;

void toggle_up() {
    // funkcja ustawia "kierunek w dół" lub "w góre"

	if (up) {	
		up = 0;
	}
	else {
		up = 1;
	}
}

ISR(TIMER0_OVF_vect) {
	++counter;
	if (counter > 9) { // to się wykonuje jeśli przerwanie wywoła się 10 razy,
                       // czyli biorąc pod uwagę częstotliwość generatora, co
                       // około 20 ms
		counter = 0;

        // tu analogicznie robimy jak w którymś z poprzednich laboratoriów
		if (up)
			OCR0 +=2;
		else
			OCR0 -=2;
	}

    // tu decudujemy, czy OCR0 mamy zmniejszań czy zwiększać
	if (OCR0 == 254)
		toggle_up();
	if (OCR0 == 2)
		toggle_up();
}

int main() {
	DDRB |= (1<<DDB3); // ustawiamy na wyjście port OC0

    //ustawiamy timer
	TIMSK |= (1<<TOIE0);
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<COM00) | (1<<CS01); 


	sei();
	while (1) {}
}
