#include <Arduino.h>

#include "clock1.h"
#include "ram.h"

#define MAINLOOP_USEC 2000
#define LOOP_TIME_MS 2
#define LOOPS_PER_SECOND 500
#define MS_TO_LOOP(ms) ((ms) / LOOP_TIME_MS)

#define ABS(a) ((a) < 0 ? -(a) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define LIMIT(x, min, max)  (((x) < (min)) ? (min) : (((x) < (max)) ? (x) : (max)))

#define PT1(new_val, old_val, time_constant_ms) ((old_val) + ((new_val) - (old_val)) / MS_TO_LOOP(time_constant_ms))
   
void setupWifi();
void setupOta();
void setupClock();
void setupSensors();
void setupControl();
void setupStepper();
void setupUI();
void setupInputOutput();

void loopOta();
void loopSensors();
void loopControl();
void loopStepper();
void loopUI();
void loopInputOutput();

void ledColor(uint8_t r, uint8_t g, uint8_t b);
