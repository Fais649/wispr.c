#include "dock_manager.h"

void DockManager::addApp(Application *app)
{
    apps.push_back(app);
    appNames.push_back(app->getAppName()); // Using typeid to get a unique name for each app
}

void DockManager::removeApp(Application *app)
{
    auto it = std::find(apps.begin(), apps.end(), app);
    if (it != apps.end())
    {
        int index = std::distance(apps.begin(), it);
        apps.erase(it);
        appNames.erase(appNames.begin() + index); // Optional: Remove the corresponding app name
    }
}

void DockManager::render()
{
    Serial.println("ENTER RENDER");
    display.setWindow(display.width() * 0.25, display.height() - dockHeight, display.width() * 0.50, dockHeight);
    if (!isDirty)
    {
        return;
    }
    Serial.println("WINDOW SET");

    int x = 60;
    int y = display.height() - dockHeight * 1.1;
    int dockWidth = display.width() * 0.3;
    int round = dockHeight / 2;

    // if (!windowManager->hasActiveWindow())
    // {
    //     Serial.println("NO ACTIVE WINDOW");
    //     display.setEpdMode(epd_fastest);
    //     display.setWindow(0, 0, display.width(), display.height() - dockHeight);
    //     display.fillRect(0, 0, display.width(), display.height() - dockHeight, TFT_BLACK);
    //     display.display();
    //     display.display();
    //     display.display();
    // }

    int iconX = x + 70 * apps.size() - 35;
    display.fillRoundRect(-x, y, display.width() * 0.275, dockHeight, round, TFT_WHITE);
    for (size_t i = 0; i < apps.size(); ++i)
    {
        int circleRadius = dockHeight / 3;
        iconX = x + 70 * i + 35;
        int iconY = y + dockHeight / 2;

        if (i == selectedAppIndex)
        {
            display.fillCircle(iconX, iconY, 20, TFT_BLACK);
            display.fillCircle(iconX, iconY, circleRadius * .75, TFT_WHITE);
            display.setEpdMode(epd_fastest);
        }
        else
        {
            display.fillCircle(iconX, iconY, 20, TFT_BLACK);
        }

        display.setTextColor(TFT_WHITE, TFT_BLACK);
        display.setCursor(iconX, iconY + dockHeight + 2);
    }

    m5::rtc_date_t date;
    M5.Rtc.getDate(&date);
    String year = String(date.year);
    String month = String(date.month);
    String day = String(date.date);

    display.setTextSize(3);
    display.setTextColor(TFT_BLACK, TFT_WHITE);

    String battery = String(M5.Power.getBatteryLevel());

    display.fillRoundRect(display.width() * 0.65, y + dockHeight * 0.1, display.width() * 0.5, dockHeight * 0.95, dockHeight * .5, TFT_WHITE);
    display.drawString(battery + "% ; " + year + "-" + month + "-" + day, display.width() * 0.68, (y + dockHeight * 0.35));

    if (isFirstRender)
    {
        display.setEpdMode(epd_fastest);
        isFirstRender = false;
    }

    display.display();
    display.display();
    display.display();
    isDirty = false;
}

void DockManager::handleTouchEvent(int x, int y)
{
    if (x < dockHeight)
    {
        int index = (y / (60)) - 1;
        if (index >= 0 && index < apps.size() && y >= 40)
        {
            if (index == selectedAppIndex)
            {
                Serial.println("REMOVE WINDOW");
                windowManager->removeWindow(apps[index]);
                windowManager->setDirty();
                windowManager->render();
                delay(50);
                selectedAppIndex = -1;
            }
            else
            {
                selectedAppIndex = index;
                windowManager->addWindow(apps[index]);
                windowManager->switchToWindow(apps[index]); // Switch to the selected app
            }
            setDirty();
            render();
        }
    }
}

void DockManager::setDirty()
{
    isDirty = true;
}