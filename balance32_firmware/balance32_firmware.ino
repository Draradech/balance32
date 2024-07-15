#include "stdinc.h"

void setup()
{
  setupWifi();
  setupOta();
  setupClock();

  setupSensors();
  setupControl();
  setupStepper();
  setupUI();
  setupInputOutput();
}

void loop()
{
  if(clk.expired())
  {
    loopSensors();
    loopControl();
    loopStepper();
    loopUI();
    loopInputOutput();
  }
  loopOta();
}
