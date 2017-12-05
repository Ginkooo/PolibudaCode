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

volatile char curr_num = 0;
volatile char code = 0;
volatile char x = 0;

int get_key_code() {
	cli();
	PORTA = 0b11101111;
	_delay_ms(1);

	MAKE_SURE

	switch(x) {
		case 0b11111110: return 1; //kolumna 1 klawisz 1
		case 0b11111101: return 5; 
		case 0b11111011: return 9; 
		case 0b11110111: return 13; 
	}

	PORTA = 0b11011111;
	_delay_ms(1);
	
	MAKE_SURE

	switch(x) {
		case 0b11111110: return 2; //kolumna 2 klawisz 1
		case 0b11111101: return 6; 
		case 0b11111011: return 10; 
		case 0b11110111: return 14; 
	}
	PORTA = 0b10111111;
	_delay_ms(1);

	MAKE_SURE

	switch(x) {
		case 0b11111110: return 3; //kolumna 3 klawisz 1
		case 0b11111101: return 7; 
		case 0b11111011: return 11; 
		case 0b11110111: return 15; 
	}
	PORTA = 0b01111111;
	_delay_ms(1);
	MAKE_SURE
	switch(x) {
		case 0b11111110: return 4; //kolumna 4 klawisz 1
		case 0b11111101: return 8; 
		case 0b11111011: return 12; 
		case 0b11110111: return 16; 
	}
	return 0;
}

void _LCD_Send(char znak) {
	SEN
	LCD_PORT = (znak & 0xF0)|(LCD_PORT & 0x0F);
	CEN
	asm volatile("nop");
	SEN
	LCD_PORT = ((znak & 0x0F)<<4)|(LCD_PORT & 0x0F);
	CEN
}


void LCD_Send(char byte, char mode) {
	if (mode == COMMAND)
		CRS
	else
		SRS
	_LCD_Send(byte);
	_delay_ms(1);
}

void LCD_Clear() {
	CRS
	LCD_Send(1, COMMAND);
	SRS
	_delay_ms(1.64);
}

void LCD_Init() {
	LCD_Send(0x02, COMMAND);
	LCD_Send(0x0C, COMMAND);
	LCD_Send(0x28, COMMAND);
	LCD_Clear();
}

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

void LCD_Shift(char direction) {
	if (direction == RIGHT)
		LCD_Send(0x14, COMMAND);
	else
		LCD_Send(0x10, COMMAND);
}

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

ISR(INT0_vect) {
	code = get_key_code();
	sei();
	curr_num = code;;
	PORTA = 0b00001111;
}

int main(void) {
	DDRA= 0xF0;
	PORTA = 0b00001111;

	MCUCR |= 1<<ISC01;
	MCUCR &= ~(1<<ISC00);
	GICR |= 1<<INT0; // w??czamy int0
	sei(); // To nie wiem czy ju? jest potrzebne


	LCD_DDR = 0xff;
	LCD_Init();
	char text[] = "Some text longer than usual";
	for (char i=0; i<0; ++i) {
		LCD_Shift(RIGHT);
	}
	_delay_ms(2000);
	LCD_Clear();

	char count = LCD_DefineSymbols();
	while(1) {
		for(int i=0; i<count; ++i) {
			LCD_Send(i, DATA);
			LCD_Send(0xC0, COMMAND);
			LCD_SendString("przycisk nr: ");
			if (curr_num < 10)
				LCD_Send(curr_num + 48, DATA);
			else {
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
}
