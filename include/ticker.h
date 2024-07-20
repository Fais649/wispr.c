#ifndef TICKER_H
#define TICKER_H

#include "dock_manager.h"
#include "global_includes.h"

#define SLEEP_TIMEOUT 90 * 1000
#define UPDATE_BATTERY_TIMEOUT 3600 * 1000

extern int lastBatteryUpdate;
extern bool _is_charging;
extern bool _was_charging;
extern bool _update_battery_once;

class Ticker {
public:
  Ticker(DockManager *dockManager) : dockManager(dockManager) {};
  void checkBattery();
  void checkSleep();

private:
  DockManager *dockManager;
};

#endif
