#include "stdinc.h"
#include <FastLED.h>

CRGB leds[1];

void setupUI()
{
  FastLED.addLeds<WS2812B, 32, GRB>(leds, 1);
}

void ledColor(uint8_t r, uint8_t g, uint8_t b)
{
  leds[0] = CRGB(r, g, b);
  FastLED.show();
}

void loopUI()
{
    static uint8_t cnt = 0;
    static uint8_t r = 0;
    cnt++;
    cnt %= 23;
    if (! cnt)
    {
      ledColor(r++, 0, 0);
    }
}
