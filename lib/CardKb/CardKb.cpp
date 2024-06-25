#include "CardKb.h"

void CardKb::scan()
{
    Wire.requestFrom(CARDKB_ADDR, 1);
    if (Wire.available()) {
        char reading = Wire.read();
        int isKey = (int)reading;
        if (reading != 0) {
            _lastChar = reading;
            _keyboard.pressKey();
        }
    }
}

char CardKb::getChar()
{
    return _lastChar;
}

bool CardKb::isKeyPressed()
{
    return _keyboard.isKeyPressed();
}