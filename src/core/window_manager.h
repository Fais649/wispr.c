#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "global_includes.h"

class WindowManager
{
public:
    void addWindow(Application *app);
    void removeWindow(Application *app);
    void switchToWindow(Application *app);
    void render();
    void handleKeyPress(const char *key);
    void setDirty();
    bool isDirty = true; // Add a dirty flag
    bool hasActiveWindow();

private:
    std::vector<Application *> windows;
    Application *activeWindow;
};

#endif