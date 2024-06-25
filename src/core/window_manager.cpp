#include "window_manager.h"

void WindowManager::addWindow(Application *app)
{
    windows.push_back(app);
}

bool WindowManager::hasActiveWindow()
{
    return activeWindow != nullptr;
}

void WindowManager::removeWindow(Application *app)
{
    auto it = std::find(windows.begin(), windows.end(), app);
    if (it != windows.end())
    {
        windows.erase(it);
        if (activeWindow == app)
        {
            Serial.println("ACTIVE WINDOW TOGGLED");
            activeWindow = windows.empty() ? nullptr : windows.front();
            if (activeWindow == nullptr)
            {
                Serial.println("ACTIVE WINDOW NULL");
            }
            else
            {
                Serial.println("ACTIVE WINDOW NOT NULL");
            }
        }
        setDirty();
    }
}

void WindowManager::switchToWindow(Application *app)
{
    removeWindow(activeWindow);
    auto it = std::find(windows.begin(), windows.end(), app);
    if (it != windows.end())
    {
        activeWindow = app;
        setDirty();
    }
}

void WindowManager::render()
{
    if (isDirty)
    {
        if (activeWindow != nullptr)
        {
            activeWindow->render();
        }
        else
        {
            Serial.println("CLEARING WINDOW");
            display.fillRect(0, 0, M5EPD_DISPLAY_WIDTH, M5EPD_DISPLAY_HEIGHT - M5EPD_DOCK_HEIGHT*1.3, TFT_BLACK);
            display.display();
        }
        isDirty = false; // Reset the dirty flag after rendering
    }
}

void WindowManager::handleKeyPress(const char *key)
{
    if (activeWindow != nullptr)
    {
        activeWindow->handleKeyPress(key);
    }
}

void WindowManager::setDirty()
{
    isDirty = true;
}