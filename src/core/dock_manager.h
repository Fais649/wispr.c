#ifndef DOCK_MANAGER_H
#define DOCK_MANAGER_H

#include "global_includes.h"
#include "core/application.h"
#include "core/window_manager.h"

class DockManager
{
public:
    DockManager(WindowManager *wm) : windowManager(wm) {}
    void addApp(Application *app);
    void removeApp(Application *app);
    void render();
    void handleTouchEvent(int x, int y);
    void setDirty();

private:
    std::vector<Application *> apps;
    std::vector<AppName> appNames; // Optional: Store app names for rendering
    int dockHeight = M5EPD_DOCK_HEIGHT;             // Example icon size
    int selectedAppIndex = -1;
    bool isDirty = true;
    bool isFirstRender = true;
    WindowManager *windowManager; // Reference to the WindowManager
};

#endif // DOCK_MANAGER_H