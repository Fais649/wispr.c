#ifndef APP_MANAGER_H
#define APP_MANAGER_H

#include "global_includes.h"

class AppManager {
public:
  void addApp(Application *app);
  void removeApp(Application *app);
  void switchToApp(Application *app);
  void render();
  void handleKeyPress(const char *key);
  void setDirty();
  bool isDirty = true; // Add a dirty flag
  bool hasActiveApp();

private:
  std::vector<Application *> apps;
  Application *activeApp;
};

#endif