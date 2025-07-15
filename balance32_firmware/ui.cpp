#include "stdinc.h"
#include <FastLED.h>

CRGB leds[1];

void setupUI()
{
  FastLED.addLeds<WS2812B, 32, GRB>(leds, 1);
  pinMode(34, INPUT_PULLUP);
  ledColor(127, 0, 0);
}

void ledColor(uint8_t r, uint8_t g, uint8_t b)
{
  leds[0] = CRGB(r, g, b);
  FastLED.show();
}

void loopUI()
{
    static int8_t cnt = 0;
    static uint8_t dis_last = 0;
    if (digitalRead(34) == 0)
    {
      cnt++;
      if (cnt > 14) cnt = 14;
      if (cnt == 7)
      {
        controlState.opMode = !controlState.opMode;
        if (controlState.opMode == 0) ledColor(96, 0, 0);
        else if (actuator.disabled == 1) ledColor(96, 48, 0);
        else ledColor(0, 48, 0);
      }
    }
    else
    {
      cnt--;
      if (cnt < 0) cnt = 0;
    }
    if (dis_last != actuator.disabled)
    {
      dis_last = actuator.disabled;
      if (controlState.opMode == 0) ledColor(96, 0, 0);
      else if (actuator.disabled == 1) ledColor(96, 48, 0);
      else ledColor(0, 48, 0);
    }
}
