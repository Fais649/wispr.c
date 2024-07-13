// #include "window_manager_task.h"

// AppManagerTask::AppManagerTask(const char *name, UBaseType_t priority,
//                                uint32_t stackSize, uint8_t core)
//     : taskName(name), taskPriority(priority), taskStackSize(stackSize),
//       taskHandle(nullptr), taskCore(core) {
//   xTaskCreatePinnedToCore(taskFunctionWrapper, taskName, taskStackSize, this,
//                           taskPriority, &taskHandle, taskCore);
//   dockManager = new DockManager(&appManager);
//   app1 = appLoader.loadApp(AppName::TODO);
//   app2 = appLoader.loadApp(AppName::NOTE);
//   appManager.addApp(app1);
//   dockManager->addApp(app1);
//   appManager.addApp(app2);
//   dockManager->addApp(app2);
//   dockManager->render();
// }

// void AppManagerTask::taskFunctionWrapper(void *parameter) {
//   AppManagerTask *task = static_cast<AppManagerTask *>(parameter);
//   task->taskFunction();
// }

// void AppManagerTask::taskFunction() {
//   while (true) {
//     if (keyboardBuffer.isUpdate()) {
//       appManager.handleKeyPress(keyboardBuffer.getBuffer().c_str());
//     }

//     appManager.render();
//     vTaskDelay(100 / portTICK_PERIOD_MS);
//   }
// }

// AppManagerTask *appManagerTask;