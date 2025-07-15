#include "stdinc.h"

#include <SPI.h>
#include <driver/ledc.h>
#include <soc/ledc_struct.h>

void spiInit()
{
  pinMode(17, OUTPUT);
  digitalWrite(17, HIGH);
  delayMicroseconds(1);
  SPI.begin();
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE3));
}

void spiTerminate()
{
  SPI.endTransaction();
}

void spiSend(uint8_t addr, uint32_t data)
{
  uint8_t* byte_data = (uint8_t *)&data;
  digitalWrite(17, LOW);
  SPI.transfer(0x80 + addr);
  SPI.transfer(byte_data[3]);
  SPI.transfer(byte_data[2]);
  SPI.transfer(byte_data[1]);
  SPI.transfer(byte_data[0]);
  digitalWrite(17, HIGH);
  delayMicroseconds(1);
}

uint32_t spiRead(uint8_t addr)
{
  uint32_t data;
  uint8_t* byte_data = (uint8_t *)&data;
  digitalWrite(17, LOW);
  SPI.transfer(addr);
  SPI.transfer(0);
  SPI.transfer(0);
  SPI.transfer(0);
  SPI.transfer(0);
  digitalWrite(17, HIGH);
  delayMicroseconds(1);
  digitalWrite(17, LOW);
  SPI.transfer(0);
  byte_data[3] = SPI.transfer(0);
  byte_data[2] = SPI.transfer(0);
  byte_data[1] = SPI.transfer(0);
  byte_data[0] = SPI.transfer(0);
  digitalWrite(17, HIGH);
  delayMicroseconds(1);
  return data;
}

#define PREC_BITS LEDC_TIMER_8_BIT

ledc_timer_config_t ledc_timer = {
    .speed_mode       = LEDC_HIGH_SPEED_MODE,
    .duty_resolution  = PREC_BITS,
    .timer_num        = LEDC_TIMER_0,
    .freq_hz          = 1000,
    .clk_cfg          = LEDC_USE_APB_CLK
};

ledc_channel_config_t ledc_channel = {
    .gpio_num       = 13,
    .speed_mode     = LEDC_HIGH_SPEED_MODE,
    .channel        = LEDC_CHANNEL_0,
    .intr_type      = LEDC_INTR_DISABLE,
    .timer_sel      = LEDC_TIMER_0,
    .duty           = (1 << (PREC_BITS - 1)) - 1,
    .hpoint         = 0
};

void setupStepper()
{
  actuator.disabled = true;
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  digitalWrite(12, actuator.disabled);

  ledc_timer_config(&ledc_timer);
  ledc_channel_config(&ledc_channel);
}

void configStepper()
{
  spiInit();
  spiSend(0x00, 0x00000004); // GCONF: en_pwm_mode=1, I_scale_analog=0
  spiSend(0x10, 0x00060F07); // IHOLD_IRUN: IHOLD=7, IRUN=15 (1/2 current), IHOLDDELAY=6
  spiSend(0x11, 0x0000000A); // TPOWERDOWN: 10 (delay before power down in stand still)
  spiSend(0x6C, 0x010300C3); // CHOPCONF: MRES=1, vsense=1, TOFF=3, HSTRT=4, HEND=1, TBL=2, CHM=0 (spreadCycle)   
  spiSend(0x70, 0x00050480); // PWM_CONF: AUTO=1, 2/683 Fclk, Switch amplitude limit=128, Grad=4
  spiTerminate();
}

int cnt;
void loopStepper()
{
  if (cnt <= 50)
  {
    if (cnt == 50)
    {
      configStepper();
    }
    cnt++;
  }

  digitalWrite(12, actuator.disabled);
  if (actuator.disabled || actuator.currentSpeed == 0)
  {
    ledc_timer_pause(LEDC_HIGH_SPEED_MODE, LEDC_TIMER_0);
    ledc_timer_rst(LEDC_HIGH_SPEED_MODE, LEDC_TIMER_0);
  }
  else
  {
    ledc_timer_resume(LEDC_HIGH_SPEED_MODE, LEDC_TIMER_0);
    int32_t prec = 1 << PREC_BITS;
    int32_t freq = actuator.currentSpeed;
    freq = ABS(freq);
    freq = MAX(1, freq);
    digitalWrite(14, actuator.currentSpeed > 0);
    actuator.clockDiv = (((uint64_t)80000000 << 8) + ((freq * prec) / 2)) / (freq * prec);
    actuator.clockDiv = LIMIT(actuator.clockDiv, 0x100, 0x3FFFF);
    LEDC.timer_group[0].timer[0].conf.clock_divider = actuator.clockDiv;
  }
}
