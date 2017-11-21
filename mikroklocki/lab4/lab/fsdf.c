#include <avr/io.h>
#include <avr/delay.h>

void delay() {
	TCNT0 = 155; // Wpisanie wartości o 100 mniejszej niż wartość MAX TCNT0
	TCCR0 |= (1<<CS00) | (1<<CS02); // Ustawienie preskalera 1024,
                                    //żeby inkrementacja licznika twrała mniej więcej milisekundę
	while (!(TIFR & 1)) {} // Czekamy dopóki licznik nie jest przepełniony
	TCCR0 &= ~((1<<CS00) | (1<<CS02)); // Wyłączamy licznik - bez tego licznik może nie działać poprawnie
	TIFR |= 1; // Gasimy flagę przepełnienia licznika - wada w architekturze mikroprocesora
               // wymusza na nas stosowanie innej operacji niż AND, np OR lub XOR
}

int main() {
	DDRB = 0x01; // Pierwszy pin PB na wyjście
	while(1) {
		delay(); // Wywołujemy opóźnienie
		PORTB ^= 1; // Migamy diodą
	}
}
