#include "app_manager.h"

void AppManager::addApp(Application *app) { apps.push_back(app); }

bool AppManager::hasActiveApp() { return activeApp != nullptr; }

void AppManager::removeApp(Application *app) {
  auto it = std::find(apps.begin(), apps.end(), app);
  if (it != apps.end()) {
    apps.erase(it);
    if (activeApp == app) {
      Serial.println("ACTIVE APP TOGGLED");
      activeApp = apps.empty() ? nullptr : apps.front();
      if (activeApp == nullptr) {
        Serial.println("ACTIVE APP NULL");
      } else {
        Serial.println("ACTIVE APP NOT NULL");
      }
    }
    setDirty();
  }
}

void AppManager::switchToApp(Application *app) {
  removeApp(activeApp);
  auto it = std::find(apps.begin(), apps.end(), app);
  if (it != apps.end()) {
    activeApp = app;
    setDirty();
  }
}

void AppManager::render() {
  if (isDirty) {
    if (activeApp != nullptr) {
      activeApp->drawWindow();
      activeApp->render(true);
    } else {
      Serial.println("CLEARING APP");
      display.fillRect(0, 0, M5EPD_DISPLAY_WIDTH,
                       M5EPD_DISPLAY_HEIGHT - M5EPD_DOCK_HEIGHT * 1.3,
                       TFT_BLACK);
      display.display();
    }
    isDirty = false;
  }
}

void AppManager::handleKeyPress(const char *key) {
  if (activeApp != nullptr) {
    activeApp->handleKeyPress(key);
  }
}

void AppManager::setDirty() { isDirty = true; }