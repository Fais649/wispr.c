#include "keyboard_task.h"

KeyboardTask::KeyboardTask(const char *name, UBaseType_t priority,
                           uint32_t stackSize, uint8_t core)
    : taskName(name), taskPriority(priority), taskStackSize(stackSize),
      taskHandle(nullptr), taskCore(core) {
  xTaskCreatePinnedToCore(taskFunctionWrapper, taskName, taskStackSize, this,
                          taskPriority, &taskHandle, taskCore);
}

void KeyboardTask::taskFunctionWrapper(void *parameter) {
  KeyboardTask *task = static_cast<KeyboardTask *>(parameter);
  task->taskFunction();
}

void KeyboardTask::taskFunction() {
  while (true) {
    keyboard.scan();
    if (keyboard.isKeyPressed()) {
      keyboardBuffer.addChar(keyboard.getChar());
    }
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

KeyboardTask *keyboardTask;
