#include "keyboard_buffer.h"

KeyboardBuffer::KeyboardBuffer() : index(0) {
  mutex = xSemaphoreCreateMutex();
  memset(buffer, 0, BUFFER_SIZE);
  buffer[0] = '\0';
  _update = false;
}

void KeyboardBuffer::addChar(char c) {
  xSemaphoreTake(mutex, portMAX_DELAY);
  _update = true;
  if (index < BUFFER_SIZE - 1) {
    buffer[index] = c;
    index++;
    buffer[index] = '\0';
  }
  xSemaphoreGive(mutex);
}

String KeyboardBuffer::getBuffer() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  String result(buffer);
  memset(buffer, 0, BUFFER_SIZE);
  buffer[0] = '\0';
  index = 0;
  _update = false;
  xSemaphoreGive(mutex);
  return result;
}

bool KeyboardBuffer::isUpdate() { return _update; }

KeyboardBuffer keyboardBuffer;