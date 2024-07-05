#include "window_manager_task.h"

WindowManagerTask::WindowManagerTask(const char *name, UBaseType_t priority,
                                     uint32_t stackSize, uint8_t core)
    : taskName(name), taskPriority(priority), taskStackSize(stackSize),
      taskHandle(nullptr), taskCore(core) {
  xTaskCreatePinnedToCore(taskFunctionWrapper, taskName, taskStackSize, this,
                          taskPriority, &taskHandle, taskCore);
  dockManager = new DockManager(&windowManager);
  app1 = appLoader.loadApp(AppName::TODO);
  app2 = appLoader.loadApp(AppName::NOTE);
  windowManager.addWindow(app1);
  dockManager->addApp(app1);
  windowManager.addWindow(app2);
  dockManager->addApp(app2);
  dockManager->render();
}

void WindowManagerTask::taskFunctionWrapper(void *parameter) {
  WindowManagerTask *task = static_cast<WindowManagerTask *>(parameter);
  task->taskFunction();
}

void WindowManagerTask::taskFunction() {
  while (true) {
    if (keyboardBuffer.isUpdate()) {
      windowManager.handleKeyPress(keyboardBuffer.getBuffer().c_str());
    }

    windowManager.render();
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

WindowManagerTask *windowManagerTask;