#include "dock_manager.h"
#include <Preferences.h>

Preferences savedDock;

float circleRadius =
    (Layout::dock_height_abs - (2 * Layout::dock_content_y_padding_abs)) * 0.5;

float selectedCircleRadius = circleRadius * 0.75;

float iconX =
    Layout::dock_x_abs + Layout::dock_content_x_padding_abs + circleRadius;
float iconY =
    Layout::dock_y_abs + Layout::dock_content_y_padding_abs + circleRadius;

void DockManager::addApp(Application *app) {
  apps.push_back(app);
  appNames.push_back(app->getAppName());
}

void DockManager::removeApp(Application *app) {
  auto it = std::find(apps.begin(), apps.end(), app);
  if (it != apps.end()) {
    int index = std::distance(apps.begin(), it);
    apps.erase(it);
    appNames.erase(appNames.begin() + index);
  }
}

void DockManager::render(bool fullRender) {
  if (!isDirty) {
    return;
  }

  if (fullRender) {
    display.fillRoundRect(Layout::dock_x_abs, Layout::dock_y_abs,
                          Layout::dock_width_abs, Layout::dock_height_abs,
                          Layout::dock_border_radius_abs, TFT_WHITE);
    updateDateBattery();
  }

  float newIconX = iconX;
  for (size_t i = 0; i < apps.size(); ++i) {
    newIconX = newIconX +
               (i * (Layout::dock_content_x_padding_abs + (circleRadius * 2)));
    iconsX[i] = newIconX;

    if (i == selectedAppIndex) {
      display.fillCircle(newIconX, iconY, circleRadius, TFT_BLACK);
      display.fillCircle(newIconX, iconY, selectedCircleRadius, TFT_WHITE);
      display.setEpdMode(Layout::display_mode_fastest);
    } else {
      display.fillCircle(newIconX, iconY, circleRadius, TFT_BLACK);
    }
  }

  display.display();
  isDirty = false;
}

void DockManager::updateDateBattery() {
  m5::rtc_date_t date;
  M5.Rtc.getDate(&date);
  String year = String(date.year);
  String month = String(date.month);
  String day = String(date.date);

  display.setTextSize(Layout::dock_text_size);
  display.setTextColor(TFT_BLACK, TFT_DARKGRAY);
  int mv = getBatteryVoltage();
  Serial.println("VOLTAGE");
  Serial.println(mv);
  String battery = String(averageBatteryLevel(mv));

  String batterySymbol = String("%");
  if (M5.Power.isCharging()) {
    batterySymbol = "|";
  }

  display.fillRoundRect(Layout::dock_right_x_abs, Layout::dock_right_y_abs,
                        Layout::dock_right_width_abs,
                        Layout::dock_right_height_abs,
                        Layout::dock_border_radius_abs, TFT_WHITE);

  display.fillRoundRect(Layout::dock_right_x_abs, Layout::dock_right_y_abs,
                        Layout::dock_right_width_abs,
                        Layout::dock_right_height_abs,
                        Layout::dock_border_radius_abs, TFT_WHITE);
  display.drawString(
      battery + batterySymbol + " < " + year + "." + month + "." + day + " >",
      Layout::dock_right_x_abs + Layout::dock_right_content_x_padding_abs,
      Layout::dock_right_y_abs + Layout::dock_right_content_y_padding_abs);
}

void DockManager::batteryBegin() {
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(BAT_ADC_CHANNEL, ADC_ATTEN_DB_12);
  _adc_chars = (esp_adc_cal_characteristics_t *)calloc(
      1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_12,
                           BASE_VOLATAGE, _adc_chars);

  uint32_t raw_value = adc1_get_raw(ADC1_CHANNEL_7);
  uint32_t measured_voltage = esp_adc_cal_raw_to_voltage(raw_value, _adc_chars);
  float actual_voltage =
      4.37 * 1000; // Convert 4.37V to mV (assuming the battery is fully charged
                   // and the full charge voltage is 4.37V)
  float scale = actual_voltage / measured_voltage;
  Serial.println("SCALE");
  Serial.println(scale);
}

uint32_t DockManager::getBatteryVoltage() {
  uint32_t adc_raw_value = 0;
  for (uint16_t i = 0; i < ADC_FILTER_SAMPLE; i++) {
    adc_raw_value += adc1_get_raw(BAT_ADC_CHANNEL);
  }

  adc_raw_value = adc_raw_value / ADC_FILTER_SAMPLE;

  uint32_t voltage =
      (uint32_t)(esp_adc_cal_raw_to_voltage(adc_raw_value, _adc_chars) / SCALE);

  filteredVoltage = ALPHA * voltage + (1 - ALPHA) * filteredVoltage;
  return voltage;
}

int DockManager::averageBatteryLevel(int mv) {
  const int minVoltage = BASE_VOLATAGE;
  const int maxVoltage = 4200;
  if (mv < minVoltage)
    mv = minVoltage;
  if (mv > maxVoltage - 20)
    mv = maxVoltage;

  int level = (mv - minVoltage) * 100 / (maxVoltage - minVoltage);
  return level;
}

void DockManager::handleTouchEvent(int x, int y) {
  if (M5.Touch.getDetail().isFlicking()) {
    //
  }
  if (y < Layout::dock_height_abs) {
    int index = 0;
    if (index >= 0 && index < apps.size()) {
      for (int i = 0; i < apps.size(); i++) {
        if (x >= iconsX[i] - circleRadius && x < iconsX[i] + circleRadius) {
          index = i;
          break;
        }
        index = 0;
      }

      if (index == selectedAppIndex) {
        Serial.println("REMOVE WINDOW");
        appManager->removeApp(apps[index]);
        appManager->setDirty();
        appManager->render();
        selectedAppIndex = -1;
      } else {
        selectedAppIndex = index;
        appManager->addApp(apps[index]);
        appManager->switchToApp(apps[index]);
      }

      Serial.println("saving selectedAppIndex: ");
      Serial.println(selectedAppIndex);
      savedDock.begin("saved_dock");
      savedDock.clear();
      savedDock.putInt("app_index", selectedAppIndex);
      savedDock.end();
      setDirty();
      render();
    }
  } else if (x > Layout::dock_right_x_abs) {
    // handle dateSwitch
  }
}

void DockManager::restoreState() {
  Serial.println("starting pref savedDock");
  savedDock.begin("saved_dock");
  selectedAppIndex = savedDock.getInt("app_index", -1);
  savedDock.clear();
  savedDock.end();

  batteryBegin();

  Serial.println("loading selectedAppIndex: ");
  Serial.println(selectedAppIndex);

  Serial.println("dockmanager::appssize ");
  Serial.println(apps.size());
  if (selectedAppIndex > -1 && selectedAppIndex < apps.size()) {
    appManager->addApp(apps[selectedAppIndex]);
    appManager->switchToApp(apps[selectedAppIndex]);
    appManager->render();
  }
  setDirty();
  render(true);
}

void DockManager::setDirty() { isDirty = true; }

void DockManager::drawSleepIcon(bool y) {
  display.setEpdMode(epd_text);
  display.setFont(Layout::dock_symbol_font);
  display.setTextColor(y ? TFT_WHITE : TFT_BLACK);
  display.setTextSize(Layout::sleep_icon_size);
  display.drawString(Layout::sleep_icon, Layout::sleep_icon_x_abs,
                     Layout::sleep_icon_y_abs);
  display.display();
  display.setEpdMode(Layout::display_mode_fastest);
  display.setFont(Layout::window_content_title_font);
}

void DockManager::loadApps() {
  Application *todoApp = appLoader->loadApp(AppName::TODO);
  Application *noteApp = appLoader->loadApp(AppName::NOTE);

  if (todoApp) {
    addApp(todoApp);
    Serial.println("main::log::noteAapp added");
  } else {
    Serial.println("main::error::todoApp is null!");
  }

  if (noteApp) {
    addApp(noteApp);
    Serial.println("main::log::noteApp added");
  } else {
    Serial.println("main::error::noteApp is null!");
  }
}
