#ifndef TYPER_H
#define TYPER_H

#include "core/app_manager.h"
#include "core/dock_manager.h"

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