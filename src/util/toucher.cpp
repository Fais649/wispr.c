#include "toucher.h"

void Toucher::checkTouch() {
  M5.update();
  M5.Touch.update(millis());
  if (M5.Touch.getDetail().wasPressed() || M5.Touch.getDetail().isPressed()) {
    Serial.println("loop::touched!");
    lastAction = millis();
    const m5::touch_point_t touch = M5.Touch.getTouchPointRaw(0);
    Serial.printf("Touch detected at x: %d, y: %d\n", touch.x, touch.y);
    dockManager->handleTouchEvent(touch.y, touch.x);
    delay(100);
  }

  if (M5.BtnA.wasPressed()) {
    display.setEpdMode(Layout::display_mode_fastest);
    display.clear(TFT_BLACK);
    display.display();
    delay(400);
    display.setEpdMode(Layout::display_mode_fastest);
    dockManager->setDirty();
    appManager->setDirty();
    dockManager->render();
    appManager->render();
    display.display();
  }
}