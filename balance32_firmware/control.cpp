#include "stdinc.h"

void setupControl()
{
  controlPara.speedP = 200;
  controlPara.speedI = 150;
  controlPara.voltageWP = (int16_t)(1.5 / 4.715e-4);
  controlPara.voltageP = 800;
  controlPara.voltageD = 200;
  controlState.opMode = 1;
  controlPara.targetSpeed = 10;
}

void loopControl()
{
  if (actuator.disabled)
  {
    actuator.currentSpeed = 0;
    controlState.targetVoltageI = 0;
  }
  controlState.targetSpeed = controlPara.targetSpeed * 1000;
  controlState.currentSpeed = actuator.currentSpeed;
  controlState.speedDeviation = controlState.targetSpeed - controlState.currentSpeed;
  controlState.targetVoltageP = -controlState.speedDeviation / 100 * controlPara.speedP / 1000;
  controlState.targetVoltageI -= controlState.speedDeviation / 100 * controlPara.speedI / 1000;
  controlState.targetVoltage = controlPara.voltageWP + controlState.targetVoltageP + controlState.targetVoltageI / 1000;
  controlState.currentVoltage = sensorData.voltage;
  controlState.voltageDeviationLast = controlState.voltageDeviation;
  controlState.voltageDeviation = controlState.targetVoltage - controlState.currentVoltage;
  controlState.accP = controlState.voltageDeviation * controlPara.voltageP / 1000;
  controlState.accD = (controlState.voltageDeviation - controlState.voltageDeviationLast) * controlPara.voltageD;
  controlState.acc = controlState.accP + controlState.accD;
  controlState.acc = LIMIT(controlState.acc, -2000, 2000);
  if (abs(controlState.accP) < 10 && controlState.opMode == 1)
  {
    actuator.disabled = 0;
  }
  if (!actuator.disabled)
  {
    actuator.currentSpeed += controlState.acc;
  }
  if (abs(actuator.currentSpeed) > 300000 || controlState.opMode != 1)
  {
    actuator.disabled = 1;
  }
}
