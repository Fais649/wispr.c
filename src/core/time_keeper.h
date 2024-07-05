#ifndef TIME_KEEPER_H
#define TIME_KEEPER_H

#include <Arduino.h>
#include <hardware.h>

class TimeKeeper
{
public:
    TimeKeeper()
    {
        m5::rtc_date_t date;
        M5.Rtc.getDate(&date);
        _year = (int)date.year;
        _month = (int)date.month;
        _day = (int)date.date;
    };
    void moveForward(int days);
    void moveBackward(int days);
    String getFormattedDate();
    String getFormattedTime();

private:
    m5::rtc_date_t _date;
    int _year;
    int _month;
    int _day;
    m5::rtc_time_t _time;
    int _hour;
    int _minute;
};

extern TimeKeeper timeKeeper;

#endif