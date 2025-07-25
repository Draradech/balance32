#include "stdinc.h"
#include <ArduinoOTA.h>

static bool done = false;
static int16_t rebootDelay = 500;

void setupOta()
{
  ArduinoOTA.setHostname("balance32");

  ArduinoOTA.onStart([]() {
    digitalWrite(12, true); // deactivate steppers
    ledColor(0, 0, 96);
  });

  ArduinoOTA.onEnd([]() {
    done = true;
  });

  ArduinoOTA.begin();
}

void loopOta()
{
  ArduinoOTA.handle();
  if(done)
  {
    if(--rebootDelay == 0)
    {
      ESP.restart();
    }
  }
}
