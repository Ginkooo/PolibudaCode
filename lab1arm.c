//zadanie2
#include <targets/AT91SAM7X256.h>

#define LCD_BACKLIGHT PIOB_SODR_P20
#define ON_BUTTON PIOB_SODR_P24
#define OFF_BUTTON PIOB_SODR_P25

#define ON_BUTTON PIOB_PDSR_P24
#define OFF_BUTTON PIOB_PDSR_P25

int main() {
  PMC_PCER = PMC_PCER_PIOB;
  PIOB_OER = LCD_BACKLIGHT;
  PIOB_PER |= LCD_BACKLIGHT;

  for(;;)
  {
    if (!(PIOB_PDSR & ON_BUTTON))
    {
        PIOB_SODR |= LCD_BACKLIGHT;
    }
    else if (!(PIOB_PDSR & OFF_BUTTON))
    {
        PIOB_CODR |= LCD_BACKLIGHT;
    }
  }
}


//zadanie3
#include <targets/AT91SAM7X256.h>

#define LCD_BACKLIGHT PIOB_SODR_P20
#define ON_BUTTON PIOB_SODR_P24
#define OFF_BUTTON PIOB_SODR_P25
#define BUZZER PIOB_SODR_P19

#define ON_BUTTON PIOB_PDSR_P24
#define OFF_BUTTON PIOB_PDSR_P25

void delay(int count) {
int i;
for(i = 0; i < count * 3000; ++i) {
  __asm__("nop");
}
}

play_buzzer(char frequency) {
  for (char i = 0; i<frequency; ++i) {
    PIOB_SODR |= BUZZER;
    delay(frequency);
    PIOB_CODR |= BUZZER;
    delay(frequency);
  }
}

int main() {
  PMC_PCER = PMC_PCER_PIOB;
  PIOB_OER = LCD_BACKLIGHT;
  PIOB_PER |= LCD_BACKLIGHT;

  PIOB_OER |= BUZZER;
  PIOB_PER |= BUZZER;

  for(;;)
  {
    if (!(PIOB_PDSR & ON_BUTTON))
    {
        PIOB_SODR |= LCD_BACKLIGHT;
        play_buzzer(1);
    }
    else if (!(PIOB_PDSR & OFF_BUTTON))
    {
        PIOB_CODR |= LCD_BACKLIGHT;
        play_buzzer(1);
    }
  }
}
