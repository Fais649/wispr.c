#include "sd_card.h"

SDCard::SDCard() : initialized(false) { mutex = xSemaphoreCreateMutex(); }

SDCard::~SDCard() { vSemaphoreDelete(mutex); }

void SDCard::begin() {
  xSemaphoreTake(mutex, portMAX_DELAY);

  if (!initialized) {
    SPI.begin(14, 13, 12, 4);
    if (SD.begin(4, SPI, 20000000)) {
      initialized = true;
      Serial.println("SD Card initialized.");
    } else {
      Serial.println("SD Card initialization failed.");
    }
  }

  xSemaphoreGive(mutex);
}

bool SDCard::isInitialized() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  bool result = initialized;
  xSemaphoreGive(mutex);
  return result;
}
