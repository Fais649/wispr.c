
#include "core/dock_manager.h"
#include "core/window_manager.h"
#include "global_includes.h"
#include "util/app_loader.h"
#include "util/state_manager.h"
#include "util/storage_manager.h"
#include <CardKb.h>
#include <esp_adc_cal.h>

WindowManager windowManager;
DockManager dockManager(&windowManager); // Pass the WindowManager reference
StateManager stateManager;
StorageManager storageManager;
AppLoader appLoader;
#define SLEEP_TIMEOUT 90 * 1000
#define UPDATE_BATTERY_TIMEOUT 3600 * 1000
int lastAction;
int lastBatteryUpdate;
bool _is_charging = false;
bool _was_charging = false;
bool _update_battery_once = false;

void setup() {
  Serial.begin(115200);
  auto cfg = M5.config();

  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER ||
      esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0) {
    cfg.clear_display = false;
  } else {
    cfg.clear_display = true;
  }

  M5.begin(cfg);
  delay(100);
  display.setRotation(1);
  display.setEpdMode(epd_fastest);
  display.setAutoDisplay(false);
  display.setFont(Layout::window_content_text_font);
  M5.Rtc.begin();

  Serial.print("Font data size: ");
  Application *app1 = appLoader.loadApp(AppName::TODO);
  Application *app2 = appLoader.loadApp(AppName::NOTE);

  if (app1) {
    dockManager.addApp(app1);
    Serial.println("app1 added");
  } else {
    Serial.println("Error: app1 is null!");
  }

  if (app2) {
    dockManager.addApp(app2);
    Serial.println("app2 added");
  } else {
    Serial.println("Error: app2 is null!");
  }

  delay(1000);
  dockManager.batteryBegin();
  lastBatteryUpdate = millis();

  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER) {
    lastAction = 0;
    Serial.println("wakeup!Timer");
    dockManager.restore();
    display.fillCircle(display.width() * .5,
                       display.height() - M5EPD_DOCK_HEIGHT / 2, 16, TFT_BLACK);
    display.display();
    Serial.println("wakeup!displayd");
  } else if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println("wakeup!ext0");
    dockManager.restore();
    Serial.println("wakeup!batteryUpdated");
    display.fillCircle(display.width() * .5,
                       display.height() - M5EPD_DOCK_HEIGHT / 2, 16, TFT_BLACK);
    display.display();
    Serial.println("wakeup!displayd");
    lastAction = millis();
  } else {
    display.clear(TFT_BLACK);
    display.display();
    display.display();
    display.display();
  }

  dockManager.render();
}

void loop() {
  _is_charging = M5.Power.isCharging();
  if (_is_charging && !_was_charging) {
    _was_charging = true;
  } else if (!_is_charging && _was_charging) {
    _was_charging = false;
    _update_battery_once = true;
  }

  if (millis() - lastBatteryUpdate >= UPDATE_BATTERY_TIMEOUT ||
      _update_battery_once) {
    Serial.println("loop::updatingBat");
    dockManager.updateDateBattery();
    display.display();
    lastBatteryUpdate = millis();
    _update_battery_once = false;
  }

  if (millis() - lastAction >= SLEEP_TIMEOUT) {
    Serial.println("loop::enteringSleep");
    display.fillCircle(display.width() * .5,
                       display.height() - M5EPD_DOCK_HEIGHT / 2, 16, TFT_WHITE);
    display.fillCircle((display.width() * .5) + 15,
                       display.height() - (M5EPD_DOCK_HEIGHT * .7), 18,
                       TFT_BLACK);
    display.display();
    Serial.println("loop::sleep!");
    long waketime = 3600000000;
    M5.Power.deepSleep(micros() + waketime, true);
  }

  keyboard.scan();
  if (keyboard.isKeyPressed()) {
    Serial.println("loop::keyPressed!");
    lastAction = millis();
    char key = keyboard.getChar();
    Serial.println("key");
    Serial.println(key);
    windowManager.handleKeyPress(&key);
  }

  M5.update();
  M5.Touch.update(millis());
  if (M5.Touch.getDetail().wasPressed() || M5.Touch.getDetail().isPressed()) {
    Serial.println("loop::touched!");
    lastAction = millis();
    const m5::touch_point_t touch = M5.Touch.getTouchPointRaw(0);
    Serial.printf("Touch detected at x: %d, y: %d\n", touch.x, touch.y);
    dockManager.handleTouchEvent(touch.y, touch.x);
    delay(100);
  }

  windowManager.render();
}
