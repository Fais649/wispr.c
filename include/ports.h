#ifndef PORTS_H
#define PORTS_H

#include <Wire.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include "globals.h"

class Ports {
public:
    Ports();
    void begin();

private:
    SemaphoreHandle_t mutex;
    void initI2C();
};

#endif
