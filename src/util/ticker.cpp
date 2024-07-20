#include "ticker.h"
#include "hal/gpio_types.h"
int lastBatteryUpdate;
bool _is_charging = false;
bool _was_charging = false;
bool _update_battery_once = false;

void Ticker::checkBattery() {
  _is_charging = M5.Power.isCharging();
  if (_is_charging && !_was_charging) {
    _was_charging = true;
  } else if (!_is_charging && _was_charging) {
    _was_charging = false;
    _update_battery_once = true;
  }

  if (millis() - lastBatteryUpdate >= UPDATE_BATTERY_TIMEOUT ||
      _update_battery_once) {
    Serial.println("main.loop::updatingBat");
    dockManager->updateDateBattery();
    display.display();
    lastBatteryUpdate = millis();
    _update_battery_once = false;
  }
}

void Ticker::checkSleep() {
  if (millis() - lastAction >= SLEEP_TIMEOUT) {
    Serial.println("main.loop::enteringSleep");
    dockManager->drawSleepIcon(true);
    Serial.println("main.loop::sleep!");
    esp_sleep_enable_ext0_wakeup(
        (gpio_num_t)M5EPD_KEY_PUSH_PIN,
        0); // Wake up when button is pressed (GPIO goes LOW)
    M5.Power.setExtOutput(false);
    M5.Power.setUsbOutput(false);
    delay(100);
    M5.Power.powerOff();
  }
}
