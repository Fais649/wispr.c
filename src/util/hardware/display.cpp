// display.cpp
#include "display.h"

Display::Display() {
  mutex = xSemaphoreCreateMutex();
  epd_driver =
      &M5.Display; // Assuming M5.Display is the M5GFX instance for the display
}

void Display::lock() {
  // xSemaphoreTake(mutex, portMAX_DELAY);
}

void Display::unlock() {
  // xSemaphoreGive(mutex);
}

void Display::begin() {
  lock();
  epd_driver->begin();
  unlock();
}

int Display::width() {
  lock();
  return epd_driver->width();
  unlock();
}

int Display::height() {
  lock();
  return epd_driver->height();
  unlock();
}

void Display::clear(uint32_t color) {
  lock();
  epd_driver->fillScreen(color);
  epd_driver->display();
  unlock();
}

void Display::drawPixel(int32_t x, int32_t y, uint32_t color) {
  lock();
  epd_driver->drawPixel(x, y, color);
  unlock();
}

void Display::fillScreen(uint32_t color) {
  lock();
  epd_driver->fillScreen(color);
  unlock();
}

void Display::setRotation(uint8_t rotation) {
  lock();
  epd_driver->setRotation(rotation);
  unlock();
}

void Display::drawBitmap(int32_t x, int32_t y, const uint8_t *bitmap, int32_t w,
                         int32_t h, uint16_t color) {
  lock();
  epd_driver->drawBitmap(x, y, bitmap, w, h, color);
  unlock();
}

void Display::drawString(const char *string, int32_t poX, int32_t poY) {
  lock();
  epd_driver->drawString(string, poX, poY);
  unlock();
}

void Display::drawString(const String &string, int32_t poX, int32_t poY) {
  lock();
  epd_driver->drawString(string, poX, poY);
  unlock();
}

void Display::display() {
  lock();
  epd_driver->waitDisplay();
  epd_driver->display();
  unlock();
}

void Display::fillRect(int32_t x, int32_t y, int32_t w, int32_t h,
                       uint32_t color) {
  lock();
  epd_driver->fillRect(x, y, w, h, color);
  unlock();
}

void Display::drawRect(int32_t x, int32_t y, int32_t w, int32_t h,
                       uint32_t color) {
  lock();
  epd_driver->drawRect(x, y, w, h, color);
  unlock();
}

void Display::drawCircle(int32_t x, int32_t y, int32_t r, uint32_t color) {
  lock();
  epd_driver->drawCircle(x, y, r, color);
  unlock();
}

void Display::fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color) {
  lock();
  epd_driver->fillCircle(x, y, r, color);
  unlock();
}

void Display::drawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1,
                       uint32_t color) {
  lock();
  epd_driver->drawLine(x0, y0, x1, y1, color);
  unlock();
}

void Display::drawTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1,
                           int32_t x2, int32_t y2, uint32_t color) {
  lock();
  epd_driver->drawTriangle(x0, y0, x1, y1, x2, y2, color);
  unlock();
}

void Display::fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1,
                           int32_t x2, int32_t y2, uint32_t color) {
  lock();
  epd_driver->fillTriangle(x0, y0, x1, y1, x2, y2, color);
  unlock();
}

void Display::drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h,
                            int32_t r, uint32_t color) {
  lock();
  epd_driver->drawRoundRect(x, y, w, h, r, color);
  unlock();
}

void Display::fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h,
                            int32_t r, uint32_t color) {
  lock();
  epd_driver->fillRoundRect(x, y, w, h, r, color);
  unlock();
}

void Display::setTextColor(uint16_t color) {
  lock();
  epd_driver->setTextColor(color);
  unlock();
}

void Display::setTextColor(uint16_t color, uint16_t backgroundColor) {
  lock();
  epd_driver->setTextColor(color, backgroundColor);
  unlock();
}

void Display::setTextSize(float size) {
  lock();
  epd_driver->setTextSize(size);
  unlock();
}

void Display::setCursor(int16_t x, int16_t y) {
  lock();
  epd_driver->setCursor(x, y);
  unlock();
}

void Display::print(const char *str) {
  lock();
  epd_driver->print(str);
  unlock();
}

void Display::printf(const char *format, ...) {
  lock();
  char buffer[256];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  epd_driver->print(buffer);
  unlock();
}

void Display::setWindow(int x, int y, int w, int h) {
  lock();
  epd_driver->setWindow(x, y, w, h);
  unlock();
}

void Display::setEpdMode(epd_mode_t epd_mode) {
  lock();
  epd_driver->setEpdMode(epd_mode);
  unlock();
}

void Display::setAutoDisplay(bool value) {
  lock();
  epd_driver->setAutoDisplay(value);
  unlock();
}

void Display::setFont(const lgfx::IFont *font) {
  lock();
  epd_driver->setFont(font);
  unlock();
}
