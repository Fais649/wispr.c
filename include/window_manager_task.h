#ifndef WINDOW_MANAGER_TASK_H
#define WINDOW_MANAGER_TASK_H

#include "core/dock_manager.h"
#include "core/window_manager.h"
#include "global_includes.h"
#include "keyboard_buffer.h"
#include "util/app_loader.h"

class WindowManagerTask {
public:
  WindowManagerTask(const char *name, UBaseType_t priority, uint32_t stackSize,
                    uint8_t core);
  ~WindowManagerTask() {
    if (taskHandle != nullptr) {
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

  AppLoader appLoader;
  WindowManager windowManager;
  DockManager *dockManager;
  Application *app1;
  Application *app2;
};

extern WindowManagerTask *windowManagerTask;

#endif