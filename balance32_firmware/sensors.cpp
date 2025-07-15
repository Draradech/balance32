#include "stdinc.h"

void setupSensors()
{
  analogSetAttenuation(ADC_6db);
  controlPara.oversample = 10;
}

void loopSensors()
{
  int32_t sum = 0;
  for(int i = 0; i < controlPara.oversample; i++)
  {
    sum += analogRead(36);
  }
  sensorData.voltageRaw = sum / controlPara.oversample;
  sensorData.voltage = PT1(sensorData.voltageRaw, sensorData.voltage, 10);
}
