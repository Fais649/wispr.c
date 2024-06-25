// #ifndef TOUCH_PANEL_H
// #define TOUCH_PANEL_H

// #include <Arduino.h>
// #include <M5Unified.h>
// #include <freertos/FreeRTOS.h>
// #include <freertos/semphr.h>

// class TouchPanel
// {
// public:
//     TouchPanel();
//     void begin(uint8_t pin_sda, uint8_t pin_scl, uint8_t pin_int);
//     bool available();
//     void update();
//     void setRotation(uint16_t rotate);
//     tp_finger_t readFinger(uint8_t num);
//     uint16_t readFingerX(uint8_t num);
//     uint16_t readFingerY(uint8_t num);
//     uint16_t readFingerID(uint8_t num);
//     uint16_t readFingerSize(uint8_t num);
//     uint8_t getFingerNum();
//     bool isFingerUp();
//     void flush();

// private:
//     GT911 gt911;
//     SemaphoreHandle_t mutex;
// };

// #endif
