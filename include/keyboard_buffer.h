#ifndef KEYBOARD_BUFFER_H
#define KEYBOARD_BUFFER_H

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#define BUFFER_SIZE 10

class KeyboardBuffer {
public:
    KeyboardBuffer();
    void addChar(char c);
    String getBuffer();
    bool isUpdate();

private:
    char buffer[BUFFER_SIZE];
    int index;
    SemaphoreHandle_t mutex;
    bool _update;
};

extern KeyboardBuffer keyboardBuffer;

#endif