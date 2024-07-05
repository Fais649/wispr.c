#ifndef BATTERY_H
#define BATTERY_H

#include "driver/adc.h"
#include "driver/gpio.h"
#include "esp_adc_cal.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "soc/adc_channel.h"
#include <Arduino.h>

class Battery {
public:
  Battery();
  void begin();
  uint32_t getBatteryRaw();
  uint32_t getBatteryVoltage();
  float getBatteryPercentage();

private:
  void initADC();

  bool is_adc_started;
  esp_adc_cal_characteristics_t *adc_chars;
  SemaphoreHandle_t mutex;

  static const adc1_channel_t BAT_ADC_CHANNEL = ADC1_GPIO35_CHANNEL;
  static const uint32_t BASE_VOLTAGE = 3600;
  static const float SCALE;
  static const uint16_t ADC_FILTER_SAMPLE = 8;
};

#endif // BATTERY_H