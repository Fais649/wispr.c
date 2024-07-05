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
  void addTask();
  void handleKeyPress(const char *key) override;

private:
  std::vector<String> tasks;
  int selectedTaskIndex = -1;
  String _task = "";
  bool _newKey = false;
  bool _newEnter = false;
  int displayWidth = M5EPD_DISPLAY_WIDTH;
  int displayHeight = M5EPD_DISPLAY_HEIGHT;
  int dockHeight = M5EPD_DOCK_HEIGHT;

  int paddingY = (displayHeight - dockHeight) * 0.05;
  int paddingX = paddingY;

  int rectWidth = displayWidth - 2 * paddingX;
  int rectHeight = (displayHeight - dockHeight) - 2 * paddingY;

  int rectX = paddingX;
  int rectY = paddingY;
  int inputHeight = 30;
};

#endif // TODO_H