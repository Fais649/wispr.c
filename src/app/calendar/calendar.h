#ifndef CALENDAR_H
#define CALENDAR_H

#include "core/application.h"

class Calendar : public Application {
public:
  AppName getAppName() { return AppName::CALENDAR; };
  void save() override;
  void load() override;
  void render(bool fullRender = false) override;
  void handleKeyPress(const char *key) override;

protected:
  String getAppTitle() override;
};

#endif