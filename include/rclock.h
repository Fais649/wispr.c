#ifndef RCLOCK_H
#define RCLOCK_H

#include <Arduino.h>
#include <Wire.h>
#include "M5Unified.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

class RClock {
public:
    RClock();
    void begin();
    void getTime(m5::rtc_time_t &time);
    void getDate(m5::rtc_date_t &date);
    void setTime(const m5::rtc_time_t &time);
    void setDate(const m5::rtc_date_t &date);
    String getFormattedTime();
    String getFormattedDate();

private:
    m5::RTC8563_Class *rtc;
    SemaphoreHandle_t mutex;
    void setInitialTime(const m5::rtc_time_t &time, const m5::rtc_date_t &date);
};

#endif 