
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
AppLoader appLoader;
DockManager dockManager(&appManager, &appLoader);
Ticker ticker(&dockManager);
Typer typer(&dockManager);
Toucher toucher(&dockManager);

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

  Serial.println("main::log::wakeup cause");
  Serial.println(esp_sleep_get_wakeup_cause());

  dockManager.loadApps();
  dockManager.batteryBegin();
  lastBatteryUpdate = millis();
  lastAction = millis();

  display.fillRect(0, 0, Layout::display_width, Layout::display_height,
                   TFT_BLACK);
  display.setEpdMode(Layout::display_mode_fastest);
  display.display();
  dockManager.drawSleepIcon(false);
  dockManager.restoreState();
}

void loop() {
  ticker.checkBattery();
  ticker.checkSleep();
  typer.checkKeyboard();
  toucher.checkTouch();

  appManager.render();
}
