#ifndef TOUCHER_H
#define TOUCHER_H

#include "app_manager.h"
#include "dock_manager.h"

class Toucher {
public:
  Toucher(DockManager *dockManager)
      : dockManager(dockManager), appManager(dockManager->getAppManager()) {};
  void checkTouch();

private:
  DockManager *dockManager;
  AppManager *appManager;
};

#endif
