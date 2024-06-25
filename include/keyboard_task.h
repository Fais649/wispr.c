#ifndef KEYBOARD_TASK_H
#define KEYBOARD_TASK_H

#include "global_includes.h"
#include "keyboard_buffer.h"

class KeyboardTask
{
public:
    KeyboardTask(const char *name, UBaseType_t priority, uint32_t stackSize, uint8_t core);
    ~KeyboardTask()
    {
        if (taskHandle != nullptr)
        {
            vTaskDelete(taskHandle);
        }
    }

protected:
    static void taskFunctionWrapper(void *parameter);

private:
    void taskFunction();
    const char *taskName;
    TaskHandle_t taskHandle;
    UBaseType_t taskPriority;
    uint32_t taskStackSize;
    uint8_t taskCore;
};

extern KeyboardTask *keyboardTask;

#endif