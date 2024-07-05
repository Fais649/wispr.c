#include "ports.h"

Ports::Ports() { mutex = xSemaphoreCreateMutex(); }

void Ports::begin() {
  xSemaphoreTake(mutex, portMAX_DELAY);

  initI2C();

  xSemaphoreGive(mutex);
}

void Ports::initI2C() {
  Wire.begin(21, 22, (uint32_t)400000U);
  Wire1.begin(25, 32, (uint32_t)400000U);
}
