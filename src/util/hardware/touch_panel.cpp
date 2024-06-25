// #include "touch_panel.h"

// TouchPanel::TouchPanel()
// {
//     mutex = xSemaphoreCreateMutex();
// }

// void TouchPanel::begin(uint8_t pin_sda, uint8_t pin_scl, uint8_t pin_int)
// {
//     xSemaphoreTake(mutex, portMAX_DELAY);
//     gt911.begin(pin_sda, pin_scl, pin_int);
//     xSemaphoreGive(mutex);
// }

// bool TouchPanel::available()
// {
//     xSemaphoreTake(mutex, portMAX_DELAY);
//     bool result = gt911.available();
//     xSemaphoreGive(mutex);
//     return result;
// }

// void TouchPanel::update()
// {
//     xSemaphoreTake(mutex, portMAX_DELAY);
//     gt911.update();
//     xSemaphoreGive(mutex);
// }

// void TouchPanel::setRotation(uint16_t rotate)
// {
//     xSemaphoreTake(mutex, portMAX_DELAY);
//     gt911.SetRotation(rotate);
//     xSemaphoreGive(mutex);
// }

// tp_finger_t TouchPanel::readFinger(uint8_t num)
// {
//     xSemaphoreTake(mutex, portMAX_DELAY);
//     tp_finger_t finger = gt911.readFinger(num);
//     xSemaphoreGive(mutex);
//     return finger;
// }

// uint16_t TouchPanel::readFingerX(uint8_t num)
// {
//     xSemaphoreTake(mutex, portMAX_DELAY);
//     uint16_t x = gt911.readFingerX(num);
//     xSemaphoreGive(mutex);
//     return x;
// }

// uint16_t TouchPanel::readFingerY(uint8_t num)
// {
//     xSemaphoreTake(mutex, portMAX_DELAY);
//     uint16_t y = gt911.readFingerY(num);
//     xSemaphoreGive(mutex);
//     return y;
// }

// uint16_t TouchPanel::readFingerID(uint8_t num)
// {
//     xSemaphoreTake(mutex, portMAX_DELAY);
//     uint16_t id = gt911.readFingerID(num);
//     xSemaphoreGive(mutex);
//     return id;
// }

// uint16_t TouchPanel::readFingerSize(uint8_t num)
// {
//     xSemaphoreTake(mutex, portMAX_DELAY);
//     uint16_t size = gt911.readFingerSize(num);
//     xSemaphoreGive(mutex);
//     return size;
// }

// uint8_t TouchPanel::getFingerNum()
// {
//     xSemaphoreTake(mutex, portMAX_DELAY);
//     uint8_t num = gt911.getFingerNum();
//     xSemaphoreGive(mutex);
//     return num;
// }

// bool TouchPanel::isFingerUp()
// {
//     xSemaphoreTake(mutex, portMAX_DELAY);
//     bool result = gt911.isFingerUp();
//     xSemaphoreGive(mutex);
//     return result;
// }

// void TouchPanel::flush()
// {
//     xSemaphoreTake(mutex, portMAX_DELAY);
//     gt911.flush();
//     xSemaphoreGive(mutex);
// }
