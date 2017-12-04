#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int get_key_code() {
	PORTA = 0b11101111;
	_delay_ms(1);
	char x = PINA | 0xf0;
	
	_delay_ms(10);
	if (x != (PINA | 0xf0)) return 0;

	switch(x) {
		case 0b11111110: return 1; //kolumna 1 klawisz 1
		case 0b11111101: return 5; 
		case 0b11111011: return 9; 
		case 0b11110111: return 13; 
	}
	PORTA = 0b11011111;
	_delay_ms(1);
	x = PINA | 0xf0;
	switch(x) {
		case 0b11111110: return 2; //kolumna 2 klawisz 1
		case 0b11111101: return 6; 
		case 0b11111011: return 10; 
		case 0b11110111: return 14; 
	}
	PORTA = 0b10111111;
	_delay_ms(1);
	x = PINA | 0xf0;
	switch(x) {
		case 0b11111110: return 3; //kolumna 3 klawisz 1
		case 0b11111101: return 7; 
		case 0b11111011: return 11; 
		case 0b11110111: return 15; 
	}
	PORTA = 0b01111111;
	_delay_ms(1);
	x = PINA | 0xf0;
	switch(x) {
		case 0b11111110: return 4; //kolumna 4 klawisz 1
		case 0b11111101: return 8; 
		case 0b11111011: return 12; 
		case 0b11110111: return 16; 
	}
	return 0;
}



ISR(INT0_vect) {
	PORTB = get_key_code(); // zapalimy odpowiednie diody przez port B
	PORTA = 0b00001111; //Spowrotem wybieramy wszystkie kolumny

    //Troch¿ po¿wiecimy diodami i je wy¿¿czymy
	_delay_ms(200);
	PORTB = 0;
}

int main() {
	DDRB = 0xFF;
	DDRA= 0xF0;
	PORTA = 0b00001111; // wybieramy wszystkie kolumny klawiatury,
                        // aby monitorowa¿ zmiany stanu wszystkich
                        // klawiszy

    // Konfigurujemy int0 na zbocze opadaj¿ce
	MCUCR |= 1<<ISC01;
	MCUCR &= ~(1<<ISC00);
	GICR |= 1<<INT0; // w¿¿czamy int0
	sei(); // To nie wiem czy ju¿ jest potrzebne
	while (1) {}
}
