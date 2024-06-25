
#include "global_includes.h"
#include "core/window_manager.h"
#include "core/dock_manager.h"
#include "util/state_manager.h"
#include "util/storage_manager.h"
#include "util/app_loader.h"
#include <CardKb.h>

WindowManager windowManager;
DockManager dockManager(&windowManager); // Pass the WindowManager reference
StateManager stateManager;
StorageManager storageManager;
AppLoader appLoader;

void setup()
{
    Serial.begin(115200); // Start serial for debugging
    M5.begin();

    display.setRotation(1);
    display.setEpdMode(epd_fastest);
    display.setAutoDisplay(false);
    display.clear(TFT_BLACK);
    display.display();
    display.display();
    display.display();

    // Load initial applications
    Application *app1 = appLoader.loadApp(AppName::TODO);
    Application *app2 = appLoader.loadApp(AppName::NOTE);
    M5.Rtc.begin();
    if (app1)
    {
        dockManager.addApp(app1);
        Serial.println("app1 added");
    }
    else
    {
        Serial.println("Error: app1 is null!");
    }

    if (app2)
    {
        dockManager.addApp(app2);
        Serial.println("app2 added");
    }
    else
    {
        Serial.println("Error: app2 is null!");
    }

    dockManager.render();
    Serial.println("dockmanager rendered!");
}

void loop()
{
    keyboard.scan();
    if (keyboard.isKeyPressed())
    {
        char key = keyboard.getChar();
        Serial.println("key");
        Serial.println(key);
        windowManager.handleKeyPress(&key);
    }

    M5.update();
    M5.Touch.update(millis());
    if (M5.Touch.getDetail().wasPressed() || M5.Touch.getDetail().isPressed())
    {
        const m5::touch_point_t touch = M5.Touch.getTouchPointRaw(0);
        Serial.printf("Touch detected at x: %d, y: %d\n", touch.x, touch.y);
        dockManager.handleTouchEvent(touch.x, touch.y);
        delay(100);
    }
    windowManager.render();
}