#ifndef TODO_H
#define TODO_H

#include "global_includes.h"

class Todo : public Application {
public:
  Todo() { load(); }
  AppName getAppName() { return AppName::TODO; };
  void save() override;
  void load() override;
  void render() override;
  void drawText();
  void drawList();
  void drawCursor(size_t i, String &currentTask, String &symbol);
  void addTask();
  void handleKeyPress(const char *key) override;

private:
  void saveLastInputs();
  std::vector<String> tasks;
  int selectedTaskIndex = -1;
  String _task = "";
  bool _newKey = false;
  bool _newEnter = false;
};

#endif // TODO_H