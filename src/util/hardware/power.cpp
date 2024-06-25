#include "power.h"

Power::Power()
{
    mutex = xSemaphoreCreateMutex();
}

void Power::begin()
{
    xSemaphoreTake(mutex, portMAX_DELAY);

    initPower();
    initSerial();

    xSemaphoreGive(mutex);
}

void Power::initPower()
{
    pinMode(M5EPD_MAIN_PWR_PIN, OUTPUT);
    enableMainPower();

    pinMode(M5EPD_EXT_PWR_EN_PIN, OUTPUT);
    pinMode(M5EPD_EPD_PWR_EN_PIN, OUTPUT);
    pinMode(M5EPD_KEY_RIGHT_PIN, INPUT);
    pinMode(M5EPD_KEY_PUSH_PIN, INPUT);
    pinMode(M5EPD_KEY_LEFT_PIN, INPUT);
    delay(100);

    enableEXTPower();
    enableEPDPower();
    delay(1000);
}

void Power::initSerial()
{
    Serial.begin(115200);
    Serial.flush();
    delay(50);
    Serial.print("M5EPD initializing...");
}
