#ifndef TODO_H
#define TODO_H

#include "global_includes.h"

class Todo : public Application {
public:
  Todo() { load(); }
  AppName getAppName() { return AppName::TODO; };
  void save() override;
  void load() override;
  void render(bool fullRender = false) override;
  void drawText(int textColor = TFT_WHITE);
  void drawList();
  void drawCursor(size_t i, String &currentTask);
  void addTask();
  void handleKeyPress(const char *key) override;

protected:
  String getAppTitle() override;

private:
  void handleNavigationKeys(char keyIn);
  void handleCharacterKey(char keyIn);
  void handleSpecialKeys(char keyIn);
  void saveLastInputs();
  std::vector<String> tasks;
  int selectedTaskIndex = -1;
  String _task = "";
  bool _newKey = false;
  bool _newEnter = false;
};

#endif // TODO_H