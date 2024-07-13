#ifndef CardKb_h
#define CardKb_h

#include "KeyboardReader.h"
#include <Arduino.h>
#include <Wire.h>

#define CARDKB_ADDR 0x5F
#define BACKSPACE 8

class CardKb
{
public:
    CardKb() { Wire.begin(18, 19, 400000U); };
    void scan();
    char getChar();
    bool isKeyPressed();
    void wakeup() { Wire.begin(18, 19, 40000U); }

private:
    char _lastChar;
    KeyboardReader _keyboard;
};

#endif
