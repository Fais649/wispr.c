#ifndef POWER_H
#define POWER_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include "globals.h"

class Power
{
public:
    Power();
    void begin();

private:
    SemaphoreHandle_t mutex;
    void initPower();
    void initSerial();
    void enableEXTPower()
    {
        digitalWrite(M5EPD_EXT_PWR_EN_PIN, 1);
    }
    void disableEXTPower()
    {
        digitalWrite(M5EPD_EXT_PWR_EN_PIN, 0);
    }
    void enableEPDPower()
    {
        digitalWrite(M5EPD_EPD_PWR_EN_PIN, 1);
    }
    void disableEPDPower()
    {
        digitalWrite(M5EPD_EPD_PWR_EN_PIN, 0);
    }
    void enableMainPower()
    {
        digitalWrite(M5EPD_MAIN_PWR_PIN, 1);
    }
    void disableMainPower()
    {
        digitalWrite(M5EPD_MAIN_PWR_PIN, 0);
    }
};

#endif
