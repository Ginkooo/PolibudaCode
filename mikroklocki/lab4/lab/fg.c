#include <avr/io.h>
#include <avr/delay.h>


int main() {
	DDRB = 0xFF; // PB na wyjście
    //Poniżej:
    //WGM - ustawiamy licznik w tryb Fast PWM
    //COM - wybieramy tryb "set OC0 on compare match, clear on TOP
    //CS - Uruchamiamy timer bez preskalera
	TCCR0 |= (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<COM00) | (1<<CS00);
    while (1) {
        for (char i=0; i<256; ++i) {
            OCR0 = i; // Ustawiamy wartość rejestru komparatora na i, które jest inkrementowane
                      // sygnał na OC0 będzie więc coraz węższy
            _delay_ms(10);
        }
        for (char i=255; i>=0; --i) {
            OCR0 = i; // Sygnał będzie coraz szerszy
            _delay_ms(10);
        }
    }
}
