#ifndef APPLICATION_H
#define APPLICATION_H

#include "global_includes.h"

enum class AppName
{
    TODO,
    NOTE,
    CALENDAR
};

class Application
{
public:
    virtual void init()
    {
        load();
    };
    virtual void save() = 0;
    virtual void load() = 0;
    virtual AppName getAppName() = 0;
    virtual void render() = 0;
    virtual void handleKeyPress(const char *key) {};
};

#endif