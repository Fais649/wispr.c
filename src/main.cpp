
#include <CardKb.h>
#include <esp_adc_cal.h>

#include "core/app_manager.h"
#include "core/dock_manager.h"
#include "global_includes.h"
#include "util/app_loader.h"
#include "util/ticker.h"
#include "util/toucher.h"
#include "util/typer.h"

AppManager appManager;
DockManager dockManager(&appManager);
Ticker ticker(&dockManager);
Typer typer(&dockManager);
Toucher toucher(&dockManager);
AppLoader appLoader;

void setup() {
  Serial.begin(115200);
  auto cfg = M5.config();
  cfg.clear_display = false;
  M5.begin(cfg);
  delay(100);
  display.setRotation(1);
  display.setEpdMode(Layout::display_mode_fastest);
  display.setAutoDisplay(false);
  display.setFont(Layout::window_content_text_font);
  M5.Rtc.begin();

  Serial.println("main.setup::wakeupcause");
  Serial.println(esp_sleep_get_wakeup_cause());

  Application *app1 = appLoader.loadApp(AppName::TODO);
  Application *app2 = appLoader.loadApp(AppName::NOTE);

  if (app1) {
    dockManager.addApp(app1);
    Serial.println("main.setup::app1 added");
  } else {
    Serial.println("main.setup::Error: app1 is null!");
  }

  if (app2) {
    dockManager.addApp(app2);
    Serial.println("main.setup::app2 added");
  } else {
    Serial.println("main.setup::Error: app2 is null!");
  }

  dockManager.batteryBegin();
  lastBatteryUpdate = millis();
  lastAction = millis();

  display.fillRect(0, 0, Layout::display_width, Layout::display_height,
                   TFT_BLACK);
  display.setEpdMode(Layout::display_mode_fastest);
  display.display();
  dockManager.drawSleepIcon(false);
  dockManager.restore();
}

void loop() {
  ticker.checkBattery();
  ticker.checkSleep();
  typer.checkKeyboard();
  toucher.checkTouch();

  appManager.render();
}
