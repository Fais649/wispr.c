#include "rclock.h"

RClock::RClock() : rtc() { mutex = xSemaphoreCreateMutex(); }

void RClock::begin() {
  // rtc->begin();
  // m5::rtc_time_t initialTime = {20, 05, 0};      // 18:12:00
  // m5::rtc_date_t initialDate = {3, 6, 12, 2024}; // Monday, June 12, 2024
  // setInitialTime(initialTime, initialDate);
}

void RClock::getTime(m5::rtc_time_t &time) { rtc->getTime(&time); }

void RClock::getDate(m5::rtc_date_t &date) { rtc->getDate(&date); }

void RClock::setTime(const m5::rtc_time_t &time) { rtc->setTime(&time); }

void RClock::setDate(const m5::rtc_date_t &date) { rtc->setDate(&date); }

void RClock::setInitialTime(const m5::rtc_time_t &time,
                            const m5::rtc_date_t &date) {
  rtc->setTime(&time);
  rtc->setDate(&date);
}

String RClock::getFormattedTime() {
  m5::rtc_time_t time;
  getTime(time);
  char timeStr[9];
  snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", time.hours, time.minutes,
           time.seconds);
  return String(timeStr);
}

String RClock::getFormattedDate() {
  m5::rtc_date_t date;
  getDate(date);
  char dateStr[11];
  snprintf(dateStr, sizeof(dateStr), "%04d-%02d-%02d", date.year, date.month,
           date.date);
  return String(dateStr);
}