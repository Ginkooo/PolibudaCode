#include <targets/AT91SAM7.h>
#include "adc.h"
#include "lcd.h"

#define AUDIO_OUT PIOB_SODR_P19
#define SW_1 PIOB_SODR_P24
#define SW_2 PIOB_SODR_P25

__attribute__ ((section(".fast")));

void delay(int n) {
  volatile int i;

  for(i=3000*n; i>0; --i) {
    __asm__("nop");
  }
}

void play_sound(int tone) {
    tone *= 10;
    PIOB_SODR |= AUDIO_OUT;
    delay(tone);
    PIOB_CODR |= AUDIO_OUT;
    delay(tone);
}

char* print_value(int n, char y, char x) {
  unsigned char bytes[5];
  bytes[4] = 0;
  bytes[3] = n % 10 + '0';
  bytes[2] = (n % 100) / 10 + '0';
  bytes[1] = (n % 1000) / 100 + '0';
  bytes[0] = (n / 1000) + '0';
  LCDPutStr(bytes, y, x, LARGE, WHITE, BLACK);
}

int main() {
  PMC_PCER = PMC_PCER_PIOB;
  PIOB_OER = AUDIO_OUT;
  PIOB_PER = AUDIO_OUT;
  InitLCD();
  InitADC();
  LCDSettings();
  LCDClearScreen();

  char step = -1;
  char prev_step = 0;
  char tmp = 0;

  char buffer[11];

  for (;;) {
    int value = GetAdcChanel(ADC_CHN_7);
    tmp = value / 100;

    print_value(value, 40, 40);

    if (tmp == prev_step) {
      continue;
    }

    step = value / 100;
    prev_step = step;

    play_sound(step);

    for (char i=0; i<=step; ++i) {
       buffer[i] = '*';
    }

    for (;step<10; ++step) {
      buffer[step] = ' ';
    }

    buffer[10] = 0;

    LCDPutStr(buffer, 10, 10, LARGE, WHITE, BLACK);
   }
}
