#ifndef CALENDAR_H
#define CALENDAR_H

#include "core/application.h"

class Calendar : public Application
{
    AppName getAppName() { return AppName::CALENDAR; };
    void save() override;
    void load() override;
    void render() override;
    void handleKeyPress(const char *key) override;
};

#endif