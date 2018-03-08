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
