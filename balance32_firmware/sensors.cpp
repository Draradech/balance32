#include "stdinc.h"

void setupSensors()
{
}

void loopSensors()
{
  sensorData.voltage = PT1(analogRead(36), sensorData.voltage, 10);
}
