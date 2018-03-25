#include <targets/AT91SAM7.h>
#include "lcd.h"

#define LCD_BACKLIGHT PIOB_SODR_P20
#define ON_BUTTON PIOB_SODR_P24
#define OFF_BUTTON PIOB_SODR_P25

#define ANIMATION 1
#define TEXT 0

void prepare_lcd() {
  PMC_PCER = PMC_PCER_PIOB;
  PIOB_OER = LCD_BACKLIGHT;
  PIOB_PER |= LCD_BACKLIGHT;
  PIOB_SODR |= LCD_BACKLIGHT;

  InitLCD();
  LCDSettings();
  LCDClearScreen();
}

char left_button_clicked() {
  return !(PIOB_PDSR & ON_BUTTON);
}

char right_button_clicked() {
  return !(PIOB_PDSR & OFF_BUTTON);
}

int main() {
   prepare_lcd();
   char display = ANIMATION;

   for(;;)
  {
    if (left_button_clicked())
    {
        LCDClearScreen();
        display = ANIMATION;
    }
    else if (right_button_clicked())
    {
        LCDClearScreen();
        display = TEXT;
    }

    if (display == ANIMATION) {
    LCDWrite130x130bmp();
    LCDWrite130x130bmp2();
    } else {
    LCDPutStr("Napis", 10, 10, LARGE, GREEN, BLACK);
    }
  }


 }
