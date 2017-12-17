#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define RS 2
#define EN 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define LCD_PORT PORTB
#define LCD_DDR DDRB

#define CEN LCD_PORT &= ~(1<<EN);
#define SEN LCD_PORT |= (1<<EN);

#define CRS LCD_PORT &= ~(1<<RS);
#define SRS LCD_PORT |= 1<<RS;

#define RIGHT 1
#define LEFT 0

#define COMMAND 1
#define DATA 0

#define LCD_WIDTH 16

#define MAKE_SURE x = (PINA | 0xf0); _delay_ms(10); if (x != (PINA | 0xf0)) return 0;

// Na górze robimy trochę makr, które ułatwią pisanie kodu


// Zmienne globalne, które wykorzystuję później
volatile char curr_num = 0;
volatile char code = 0;
volatile char x = 0;
volatile char fnum = 0;
volatile char count;
volatile force_diode_off = 0;


/**
 * @brief funkcja wyłącza diodę
 */
void turn_off_diode() {
	force_diode_off = 1; // Ta zmienna zapewnia, że dioda nie właczy się ponownie, gdy funkcja ta zostanie wywołana w jakimś przerwaniu
	PORTC = 0;
}


/**
 * @brief miganie diodą co 100 ms
 */
void _100_ms_blink() {
	TCNT0 = 150;
	TCCR0 = (1<<CS00) | (1 << CS02);
	while(!(TIFR & (1 << TOV0))) {}
	TIFR |= 1<<TOV0;
	if(!force_diode_off) PORTC ^= 1;
	TCCR0 = 0;
}


/**
 * @brief w każdym obiegu pętli wyświetla na ekranie LCD kolejną klatkę animacji,
 * 	  następnie pod spodem napis "przycisk nr:" i numer wciśniętego przycisku (odczytywanego w funkcji wywołanej przy przerwaniu klawiatury)
 */
void button_nr() {
	for(int i=0; i<count; ++i) {
		LCD_Send(i, DATA); // Wyświetl symbol i-ty animacji
		LCD_Send(0xC0, COMMAND); // Przejdź do nowej linii
		LCD_SendString("przycisk nr: ");
		if (curr_num < 10) // Jednocyfrowa liczba
			LCD_Send(curr_num + 48, DATA); // 2 -> '2' etc
		else { // Dwucyfrowa
			char f_char = curr_num / 10 + 48;
			char s_char = curr_num % 10 + 48;
			LCD_Send(f_char, DATA);
			LCD_Send(s_char, DATA);
		}
		_delay_ms(500);
		LCD_Clear();
		_delay_ms(1);
	}
}


/**
 * @brief wyświetla napis "miganie" na wyświetlaczu, wywołuje się ją gdy wybieramy z menu miganie diodą
 */
void show_blink_menu() {
LCD_Clear();
LCD_SendString("Miganie");
}


/**
 * @brief sekwencyjnie wybiera kolejne kolumny, odczytuje wciśnięty przycisk i zwraca jego numer
 *
 * @return numer przycisku
 */
int get_key_code() {
	cli(); // Wyłaczamy przerwania, by nie wywoływać przerwać niepotrzebnie, gdy będziemy iterować po kolumnach
	PORTA = 0b11101111;
	_delay_ms(1);

	MAKE_SURE // te makro odpowiada za obsługę drgać styków

	switch(x) {
		case 0b11111110: { turn_off_diode(); fnum = 0; return 1; }; // wymusza wyłaczenie diody,
				 					    // ustawia globalny wskaźnik wybranej funkcji
									    // na 0 i zwraca kod klawisza
		case 0b11111101: return 5;
		case 0b11111011: return 9;
		case 0b11110111: return 13;
	}

	PORTA = 0b11011111;
	_delay_ms(1);
	
	MAKE_SURE

	switch(x) {
		case 0b11111110: {if(fnum==0) {force_diode_off = 0; fnum = 1; show_blink_menu();} return 2;} //początkowy if zapewnia,
				 									     // że tylko z menu możemy przejść do innej funkcji
		case 0b11111101: return 6;
		case 0b11111011: return 10;
		case 0b11110111: return 14;
	}
	PORTA = 0b10111111;
	_delay_ms(1);

	MAKE_SURE

	switch(x) {
		case 0b11111110: {if(fnum==0) fnum = 2; turn_off_diode(); return 3;}
		case 0b11111101: return 7;
		case 0b11111011: return 11;
		case 0b11110111: return 15;
	}
	PORTA = 0b01111111;
	_delay_ms(1);
	MAKE_SURE
	switch(x) {
		case 0b11111110: return 4;
		case 0b11111101: return 8;
		case 0b11111011: return 12;
		case 0b11110111: return 16;
	}
	return 0;
}

/**
 * @brief wysyła podany bajt do LCD
 *
 * @param znak - bajt, który chcemy wysłać do LCD
 */
void _LCD_Send(char znak) {
	SEN
	LCD_PORT = (znak & 0xF0)|(LCD_PORT & 0x0F);
	CEN
	asm volatile("nop");
	SEN
	LCD_PORT = ((znak & 0x0F)<<4)|(LCD_PORT & 0x0F);
	CEN
}


/**
 * @brief wrapper na funcję niższego poziomu, zależnie od mode wybiera w LCD rejestr danych/rejestr komend
 *
 * @param byte - bajt, który chcemy wysłać do LCD
 * @param mode - tryb, jeden z DATA, COMMAND
 */
void LCD_Send(char byte, char mode) {
	if (mode == COMMAND)
		CRS
	else
		SRS
	_LCD_Send(byte);
	_delay_ms(1);
}

/**
 * @brief czyści ekran
 */
void LCD_Clear() {
	CRS
	LCD_Send(1, COMMAND);
	SRS
	_delay_ms(1.64);
}

/**
 * @brief przygotowywuje ekran do pracy
 */
void LCD_Init() {
	LCD_Send(0x02, COMMAND);
	LCD_Send(0x0C, COMMAND);
	LCD_Send(0x28, COMMAND);
	LCD_Clear();
}

/**
 * @brief wysyła do LCD dany string
 *
 * @param text - tablica znaków do wysłania
 */
void LCD_SendString(char *text) {
	int len = strlen(text);
	for(int i=0; i<len; i++) {
		if (i == LCD_WIDTH) {
			LCD_Send(0b11000000, COMMAND);
			if (text[i] == ' ' && (i+1<len))
				++i;
		}				
		LCD_Send(text[i], DATA);
	}
}

/**
 * @brief przesuwa kursor w podaną stronę
 *
 * @param direction - jeden z RIGHT, LEFT
 */
void LCD_Shift(char direction) {
	if (direction == RIGHT)
		LCD_Send(0x14, COMMAND);
	else
		LCD_Send(0x10, COMMAND);
}

/**
 * @brief definiujemy symbole i zwracamy liczbę klatek animacji
 *
 * @return liczba klatek animacji
 */
char LCD_DefineSymbols() {
	char symbol_count = 5;
	char tab[5][8] = {
		{
			0b00000,
			0b00000,
			0b00000,
			0b00000,
			0b00000,
			0b00000,
			0b10000
		},
		{
			0b00000,
			0b00000,
			0b00000,
			0b00000,
			0b00000,
			0b11000,
			0b01000
		},
		{
			0b00000,
			0b00000,
			0b00000,
			0b00000,
			0b11100,
			0b00100,
			0b10100
		},
		{
			0b00000,
			0b00000,
			0b00000,
			0b11110,
			0b00010,
			0b11010,
			0b01010
		},
		{
			0b00000,
			0b00000,
			0b11111,
			0b00001,
			0b11101,
			0b00101,
			0b10101
		}		
	};

	LCD_Send(0x40, COMMAND);
	char a = 0x40;
	for(int j=0; j<4; j++) {
		for(int i=0; i<=7; i++) {
			LCD_Send(a, COMMAND);
			LCD_Send(tab[j][i], DATA);
			a++;
		}
	}
	return symbol_count;
}

/**
 * @brief gdy przerwanie klawitury wystąpi, to pobieramy kod przycisku wciśniętego
 *
 */
ISR(INT0_vect) {
	code = get_key_code();
	sei(); // get_key_code musi wyłączyć przerwania, więc włączamy je ponownie
	curr_num = code; // zapisujemy w pamięci globalnej numer wciśniętego przycisku
	PORTA = 0b00001111;
}

/**
 * @brief reprezentuje menu wyboru
 */
void main_menu() {
	LCD_Clear();
	LCD_SendString("1: miganie");
	LCD_Send(0xC0, COMMAND);
	LCD_SendString("2: nr. przycisku");
	while(fnum == 0) {} // Czekaj, dopóki funkcja przerwania nie zdecyduje, że wychodzimy z menu
}

int main() {
	DDRA= 0xF0;
	DDRC = 0xff;
	PORTA = 0b00001111;

	MCUCR |= 1<<ISC01;
	MCUCR &= ~(1<<ISC00);
	GICR |= 1<<INT;
	sei();


	LCD_DDR = 0xff;
	LCD_Init();
	_delay_ms(2000);
	LCD_Clear();

	count = LCD_DefineSymbols();

	while(1) {
		switch(fnum) { // globalna zmienna, jest zawsze ustawiona na numer wybranej funkcji
			       // 0 - menu
			       // 1 - miganie
			       // 2 - który przycisk wciśnięty?
			case 2: button_nr(); break;
			case 1: _100_ms_blink(); break;
			case 0: main_menu(); break;
		}
	}	
}
