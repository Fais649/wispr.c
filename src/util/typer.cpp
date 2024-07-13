#include "typer.h"

void Typer::checkKeyboard() {
  keyboard.scan();
  if (keyboard.isKeyPressed()) {
    Serial.println("loop::keyPressed!");
    lastAction = millis();
    char key = keyboard.getChar();
    Serial.println("key");
    Serial.println(key);
    appManager->handleKeyPress(&key);
  }
}