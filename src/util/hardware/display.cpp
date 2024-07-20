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
  int w = epd_driver->width();
  unlock();
  return w;
}

int Display::height() {
  lock();
  int h = epd_driver->height();
  unlock();
  return h;
}

void Display::clear(uint32_t color) {
  lock();
  epd_driver->fillScreen(color);
  addDirtyRegion(0, 0, width(), height());
  unlock();
}

void Display::drawPixel(int32_t x, int32_t y, uint32_t color) {
  lock();
  epd_driver->drawPixel(x, y, color);
  addDirtyRegion(x, y, 1, 1);
  unlock();
}

void Display::fillScreen(uint32_t color) {
  lock();
  epd_driver->fillScreen(color);
  addDirtyRegion(0, 0, width(), height());
  unlock();
}

void Display::setRotation(uint8_t rotation) {
  lock();
  epd_driver->setRotation(rotation);
  addDirtyRegion(0, 0, width(), height());
  unlock();
}

void Display::drawBitmap(int32_t x, int32_t y, const uint8_t *bitmap, int32_t w,
                         int32_t h, uint16_t color) {
  lock();
  epd_driver->drawBitmap(x, y, bitmap, w, h, color);
  addDirtyRegion(x, y, w, h);
  unlock();
}

void Display::drawString(const char *string, int32_t poX, int32_t poY) {
  lock();
  epd_driver->fillRect(poX, poY, epd_driver->textWidth(string),
                       epd_driver->fontHeight(), TFT_BLACK);
  epd_driver->drawString(string, poX, poY);
  addDirtyRegion(poX, poY, epd_driver->textWidth(string),
                 epd_driver->fontHeight());
  unlock();
}

void Display::drawString(const String &string, int32_t poX, int32_t poY) {
  lock();
  epd_driver->fillRect(poX, poY, epd_driver->textWidth(string),
                       epd_driver->fontHeight(), TFT_BLACK);
  epd_driver->drawString(string, poX, poY);
  addDirtyRegion(poX, poY, epd_driver->textWidth(string),
                 epd_driver->fontHeight());
  unlock();
}

void Display::updateWindow() {
  lock();
  epd_driver->fillRect(Layout::window_content_x_abs,
                       Layout::window_content_text_y_abs,
                       Layout::window_content_width_abs,
                       Layout::window_content_height_abs  - Layout::window_input_height_abs - Layout::window_content_title_height_abs, TFT_BLACK);
  unlock();
}

void Display::display() {
  lock();
  for (const Rect &rect : dirtyRegions) {
    epd_driver->setWindow(rect.x, rect.y, rect.w, rect.h);
    epd_driver->display();
  }
  dirtyRegions.clear(); // Clear dirty regions after refresh
  unlock();
}

void Display::fillRect(int32_t x, int32_t y, int32_t w, int32_t h,
                       uint32_t color) {
  lock();
  epd_driver->fillRect(x, y, w, h, color);
  addDirtyRegion(x, y, w, h);
  unlock();
}

void Display::drawRect(int32_t x, int32_t y, int32_t w, int32_t h,
                       uint32_t color) {
  lock();
  epd_driver->drawRect(x, y, w, h, color);
  addDirtyRegion(x, y, w, h);
  unlock();
}

void Display::drawCircle(int32_t x, int32_t y, int32_t r, uint32_t color) {
  lock();
  epd_driver->drawCircle(x, y, r, color);
  addDirtyRegion(x - r, y - r, 2 * r, 2 * r);
  unlock();
}

void Display::fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color) {
  lock();
  epd_driver->fillCircle(x, y, r, color);
  addDirtyRegion(x - r, y - r, 2 * r, 2 * r);
  unlock();
}

void Display::drawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1,
                       uint32_t color) {
  lock();
  epd_driver->drawLine(x0, y0, x1, y1, color);
  addDirtyRegion(std::min(x0, x1), std::min(y0, y1), std::abs(x1 - x0),
                 std::abs(y1 - y0));
  unlock();
}

void Display::drawTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1,
                           int32_t x2, int32_t y2, uint32_t color) {
  lock();
  epd_driver->drawTriangle(x0, y0, x1, y1, x2, y2, color);
  addDirtyRegion(std::min({x0, x1, x2}), std::min({y0, y1, y2}),
                 std::max({x0, x1, x2}) - std::min({x0, x1, x2}),
                 std::max({y0, y1, y2}) - std::min({y0, y1, y2}));
  unlock();
}

void Display::fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1,
                           int32_t x2, int32_t y2, uint32_t color) {
  lock();
  epd_driver->fillTriangle(x0, y0, x1, y1, x2, y2, color);
  addDirtyRegion(std::min({x0, x1, x2}), std::min({y0, y1, y2}),
                 std::max({x0, x1, x2}) - std::min({x0, x1, x2}),
                 std::max({y0, y1, y2}) - std::min({y0, y1, y2}));
  unlock();
}

void Display::drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h,
                            int32_t r, uint32_t color) {
  lock();
  epd_driver->drawRoundRect(x, y, w, h, r, color);
  addDirtyRegion(x, y, w, h);
  unlock();
}

void Display::fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h,
                            int32_t r, uint32_t color) {
  lock();
  epd_driver->fillRoundRect(x, y, w, h, r, color);
  addDirtyRegion(x, y, w, h);
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
  epd_driver->fillRect(epd_driver->getCursorX(), epd_driver->getCursorY(),
                       epd_driver->textWidth(str), epd_driver->fontHeight(),
                       TFT_BLACK);
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
  epd_driver->fillRect(epd_driver->getCursorX(), epd_driver->getCursorY(),
                       Layout::window_content_width_abs -
                           epd_driver->getCursorX(),
                       epd_driver->fontHeight(), TFT_BLACK);
  epd_driver->print(buffer);
  addDirtyRegion(epd_driver->getCursorX(), epd_driver->getCursorY(),
                 epd_driver->textWidth(buffer), epd_driver->fontHeight());
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

void Display::addDirtyRegion(int32_t x, int32_t y, int32_t w, int32_t h) {
  // Merge with existing regions or add new region
  // Simple implementation to just add the region (improvements can merge
  // overlapping regions)
  dirtyRegions.push_back({x, y, w, h});
}
