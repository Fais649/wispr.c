
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
#define SLEEP_TIMEOUT 30 * 1000
#define UPDATE_BATTERY_TIMEOUT 60 * 1000
int lastAction;
int lastBatteryUpdate;

void setup() {
  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER) {
    lastAction = 0;
    Serial.println("wakeup!");
    dockManager.updateDateBattery();
    display.fillCircle(display.width() * .5,
                       display.height() - M5EPD_DOCK_HEIGHT / 2, 16, TFT_BLACK);
    display.display();
    return;
  } else if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0) {
    lastAction = millis();
    dockManager.restore();
    dockManager.updateDateBattery();
    display.fillCircle(display.width() * .5,
                       display.height() - M5EPD_DOCK_HEIGHT / 2, 16, TFT_BLACK);
    display.display();
    return;
  }

  Serial.begin(115200);
  M5.begin();
  delay(1000);
  dockManager.batteryBegin();

  display.setRotation(1);
  display.setEpdMode(epd_fastest);
  display.setAutoDisplay(false);
  display.clear(TFT_BLACK);
  display.display();
  display.display();
  display.display();

  // Load initial applications
  Application *app1 = appLoader.loadApp(AppName::TODO);
  Application *app2 = appLoader.loadApp(AppName::NOTE);
  M5.Rtc.begin();
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

  dockManager.render();
  Serial.println("dockmanager rendered!");
  lastBatteryUpdate = millis();
}

void loop() {
  if (millis() - lastBatteryUpdate >= UPDATE_BATTERY_TIMEOUT) {
    dockManager.updateDateBattery();
    display.display();
    lastBatteryUpdate = millis();
  }

  if (millis() - lastAction >= SLEEP_TIMEOUT) {
    display.fillCircle(display.width() * .5,
                       display.height() - M5EPD_DOCK_HEIGHT / 2, 16, TFT_WHITE);
    display.fillCircle((display.width() * .5) + 15,
                       display.height() - (M5EPD_DOCK_HEIGHT * .7), 18,
                       TFT_BLACK);
    display.display();
    Serial.println("sleep!");
    M5.Power.deepSleep(SLEEP_TIMEOUT * 1000, true);
  }

  keyboard.scan();
  if (keyboard.isKeyPressed()) {
    lastAction = millis();
    char key = keyboard.getChar();
    Serial.println("key");
    Serial.println(key);
    windowManager.handleKeyPress(&key);
  }

  M5.update();
  M5.Touch.update(millis());
  if (M5.Touch.getDetail().wasPressed() || M5.Touch.getDetail().isPressed()) {
    lastAction = millis();
    const m5::touch_point_t touch = M5.Touch.getTouchPointRaw(0);
    Serial.printf("Touch detected at x: %d, y: %d\n", touch.x, touch.y);
    dockManager.handleTouchEvent(touch.x, touch.y);
    delay(100);
  }
  windowManager.render();
}
