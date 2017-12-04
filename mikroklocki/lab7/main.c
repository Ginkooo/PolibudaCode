#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define RS 2
#define EN 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define LCD_PORT PORTD
#define LCD_DDR DDRD

#define CEN LCD_PORT &= ~(1<<EN);
#define SEN LCD_PORT |= (1<<EN);

#define CRS LCD_PORT &= ~(1<<RS);
#define SRS LCD_PORT |= 1<<RS;

#define RIGHT 1
#define LEFT 0

#define COMMAND 1
#define DATA 0

#define LCD_WIDTH 16

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
	for(int i; i<len; i++) {
		if (i == LCD_WIDTH) {
			LCD_Send(0xC0, COMMAND);
			if (text[i] == ' ' && (i+1<len))
				++i; //skip space in that case
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

int main(void) {
	LCD_DDR = 0xff;
	LCD_Init();
	char text[] = "Some text longer than usual";
	for (char i=0; i<0; ++i) { //2
		LCD_Shift(RIGHT);
	}
	LCD_SendString(text);
	_delay_ms(2000);
	LCD_Clear();

	char count = LCD_DefineSymbols();
	while(1) {
		for(int i=0; i<count; i++) {
			LCD_Send(i, DATA);
			_delay_ms(500);
			LCD_Clear();
			_delay_ms(1);
		}
	}
}
