#ifdef _DEFINE_RAM_VARS_
#define globl
#else
#define globl extern
#endif

typedef struct
{
  int16_t voltage;
  int16_t voltageRaw;
  int16_t cpu[5];
} SSensorData;

typedef struct
{
  int32_t currentSpeed;
  int32_t clockDiv;
  bool disabled;
} SActuator;

typedef struct
{
  int16_t oversample;
  int16_t speedP;
  int16_t speedI;
  int16_t voltageWP;
  int16_t voltageP;
  int16_t voltageD;
  int16_t targetSpeed;
} SControlPara;

typedef struct
{
  int32_t opMode;
  int32_t targetSpeed;
  int32_t currentSpeed;
  int32_t speedDeviation;
  int32_t targetVoltageP;
  int32_t targetVoltageI;
  int32_t targetVoltage;
  int32_t currentVoltage;
  int32_t voltageDeviation;
  int32_t voltageDeviationLast;
  int32_t accP;
  int32_t accD;
  int32_t acc;
} SControlState;

globl SSensorData sensorData;
globl SActuator actuator;
globl SControlPara controlPara;
globl SControlState controlState;
globl Clock1 clk;
