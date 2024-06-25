#ifndef SDCARD_H
#define SDCARD_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

class SDCard {
public:
    SDCard();
    ~SDCard();

    void begin();
    bool isInitialized();

private:
    bool initialized;
    SemaphoreHandle_t mutex;
};

#endif // SDCARD_H
