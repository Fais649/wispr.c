#ifndef DOCK_MANAGER_H
#define DOCK_MANAGER_H

#include "app_manager.h"
#include <app_loader.h>
#include "application.h"
#include "global_includes.h"
#include <esp_adc_cal.h>

#define BAT_ADC_CHANNEL ADC1_CHANNEL_7
#define BASE_VOLATAGE 3800
#define SCALE 0.5 // 0.78571429
#define ADC_FILTER_SAMPLE 50
#define ALPHA 0.1

class DockManager {
public:
  DockManager(AppManager *am, AppLoader *al) : appManager(am), appLoader(al) {}
  void addApp(Application *app);
  void removeApp(Application *app);
  void render(bool fullRender = false);
  void handleTouchEvent(int x, int y);
  void setDirty();
  void batteryBegin();
  void updateDateBattery();
  void restoreState();
  void drawSleepIcon(bool y);
  AppManager *getAppManager() { return appManager; };
  void loadApps();

private:
  int averageBatteryLevel(int samples = 10);
  uint32_t getBatteryVoltage();
  std::vector<Application *> apps;
  std::vector<AppName> appNames; // Optional: Store app names for rendering
  int selectedAppIndex = -1;
  bool isDirty = true;
  bool isFirstRender = true;
  AppManager *appManager;             // Reference to the AppManager
  AppLoader *appLoader;
  int dockHeight = M5EPD_DOCK_HEIGHT; // Example icon size
  esp_adc_cal_characteristics_t *_adc_chars;
  float filteredVoltage = 0; // Variable to store the filtered voltage
  int iconsX[2] = {0, 0};
};

#endif // DOCK_MANAGER_H
