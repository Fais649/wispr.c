#ifndef TYPER_H
#define TYPER_H

#include "app_manager.h"
#include "dock_manager.h"

class Typer {
public:
  Typer(DockManager *dockManager)
      : dockManager(dockManager), appManager(dockManager->getAppManager()) {};
  void checkKeyboard();

private:
  DockManager *dockManager;
  AppManager *appManager;
};

#endif
