// display.h
#ifndef DISPLAY_H
#define DISPLAY_H

#include "display_consts.h"
#include "globals.h"
#include <Arduino.h>
#include <M5Unified.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

class Display {
public:
  Display();
  void begin();
  int width();
  int height();
  void clear(uint32_t color = TFT_WHITE);
  void drawPixel(int32_t x, int32_t y, uint32_t color);
  void fillScreen(uint32_t color);
  void setRotation(uint8_t rotation);
  void drawBitmap(int32_t x, int32_t y, const uint8_t *bitmap, int32_t w,
                  int32_t h, uint16_t color);
  void drawString(const char *string, int32_t poX, int32_t poY);
  void drawString(const String &string, int32_t poX, int32_t poY);
  void display();
  void fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);
  void drawRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);
  void drawCircle(int32_t x, int32_t y, int32_t r, uint32_t color);
  void fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color);
  void drawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);
  void drawTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2,
                    int32_t y2, uint32_t color);
  void fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2,
                    int32_t y2, uint32_t color);
  void drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r,
                     uint32_t color);
  void fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r,
                     uint32_t color);
  void setTextColor(uint16_t color);
  void setTextColor(uint16_t color, uint16_t backgroundColor);
  void setTextSize(float size);
  void setCursor(int16_t x, int16_t y);
  void print(const char *str);
  void printf(const char *format, ...);
  void setWindow(int x, int y, int w, int h);
  void setEpdMode(epd_mode_t epd_mode);
  void setAutoDisplay(bool value);
  void setFont(const lgfx::IFont* font);
  // Add more methods as needed...

private:
  M5GFX *epd_driver;
  SemaphoreHandle_t mutex;

  void lock();
  void unlock();
};

#endif // DISPLAY_H