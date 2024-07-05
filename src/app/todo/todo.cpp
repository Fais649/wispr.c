#include "Todo.h"
#include <Preferences.h>

Preferences savedTodos;

void Todo::save() {
  savedTodos.begin("saved_todos");
  int itemCount = tasks.size();

  savedTodos.putInt("item_count", itemCount);
  for (size_t i = 0; i < itemCount; i++) {
    if (tasks[i].length() > 0) {
      savedTodos.putString("todo_item_" + i, tasks[i]);
    }
  }
  savedTodos.end();
}

void Todo::load() {
  savedTodos.begin("saved_todos");
  int itemCount = savedTodos.getInt("item_count");
  for (size_t i = 0; i < itemCount; i++) {
    String item = savedTodos.getString("todo_item_" + i);

    if (item.length() > 0) {
      tasks.push_back(item);
    }
  }
  savedTodos.end();
}

void Todo::render() {
  Serial.println("TODO RENDER");
  display.setWindow(rectX, rectY, rectWidth, rectHeight);

  if (_newKey) {
    drawText();
  } else {
    drawList();
  }

  display.display();
  display.display();
  display.display();
  save();
}

void Todo::drawText() {
  display.setEpdMode(epd_fastest);
  Serial.println("TEXT RENDER");
  Serial.println(_task);
  display.setWindow(rectX, rectY + rectHeight - inputHeight, rectWidth,
                    inputHeight);
  display.setTextSize(4);
  display.setTextColor(TFT_WHITE);
  display.fillRect(rectX + 2 * paddingX,
                   rectY + rectHeight - inputHeight - 2 * paddingY,
                   rectWidth - 4 * paddingX, inputHeight, TFT_BLACK);
  display.drawString(_task, rectX + 2 * paddingX,
                     rectY + rectHeight - inputHeight - 2 * paddingY);
  display.display();
  _newKey = false;
}

void Todo::drawList() {
  display.setEpdMode(epd_fastest);
  display.fillRoundRect(rectX - paddingX / 3, rectY + paddingY / 3, rectWidth,
                        rectHeight, 25, TFT_DARKGRAY);
  display.fillRoundRect(rectX, rectY, rectWidth, rectHeight, 25, TFT_WHITE);
  display.fillRoundRect(rectX + paddingX, rectY + paddingY,
                        rectWidth - (2 * paddingX), rectHeight - (2 * paddingY),
                        15, TFT_BLACK);

  display.setTextSize(5);
  display.setCursor(rectX + 35, rectY + 35);
  display.setTextColor(TFT_WHITE);

  display.print("todo;");

  display.setTextSize(3);

  for (size_t i = 0; i < tasks.size(); ++i) {
    String symbol = "[x]";
    String currentTask = tasks[i];
    display.setCursor(rectX + 35, (i + 1.2) * rectY + 100);
    if (i == selectedTaskIndex) {
      Serial.println("drawing list cursor");

      display.setTextColor(TFT_LIGHTGREY);
      if (currentTask.charAt(0) == '%') {
        currentTask = currentTask.substring(1);
        symbol = "---[x]";
      } else {
        symbol = "[x]";
      }

      display.printf("%s - %s\n", symbol.c_str(), currentTask.c_str());
    } else {
      if (currentTask.charAt(0) == '%') {
        currentTask = currentTask.substring(1);
        display.setTextColor(TFT_DARKGREY);
        symbol = "---[+]";
      } else {
        display.setTextColor(TFT_WHITE);
        symbol = "[" + String(i + 1) + "]";
      }

      display.printf("%s - %s\n", symbol.c_str(), currentTask.c_str());
    }
  }
}

void Todo::handleKeyPress(const char *key) {
  if (key != nullptr) {
    char keyIn = *key;
    Serial.println("todoKey");
    Serial.println(_task);
    Serial.print("Key pressed: ");
    Serial.println(*key, HEX); // Print the key in hexadecimal format

    if (keyIn == 8) {
      if (_task.length() > 0) {
        _task.remove(_task.length() - 1);
      }
      _newKey = true;
      render();
    } else if (keyIn == 0xD) {
      addTask();
      _newEnter = true;
      render();
    } else if (keyIn == 0xB5 || keyIn == 0xB6) {
      if (tasks.size() <= 0) {
        selectedTaskIndex = -1;
      } else if (keyIn == 0xB5) {
        if (selectedTaskIndex == -1) {
          selectedTaskIndex = tasks.size();
        }

        Serial.println("index++");
        if (selectedTaskIndex >= 1) {
          selectedTaskIndex--;
        }
        Serial.println(selectedTaskIndex);
      } else if (keyIn == 0xB6) {
        if (selectedTaskIndex == -1) {
          selectedTaskIndex = 0;
        }
        Serial.println("index--");
        if (selectedTaskIndex < tasks.size() - 1) {
          selectedTaskIndex++;
        }
        Serial.println(selectedTaskIndex);
      }
      render();
    } else if (keyIn == 0x7F) {
      if (selectedTaskIndex != -1) {
        tasks.erase(tasks.begin() + selectedTaskIndex);
      }

      render();
    } else if (keyIn == 0x09) {
      if (selectedTaskIndex != -1) {
        String selectedTask = tasks[selectedTaskIndex];
        if (selectedTask.charAt(0) != '%') {
          String marker = "%";
          marker.concat(selectedTask);
          selectedTask = marker;
          tasks.erase(tasks.begin() + selectedTaskIndex);
          tasks.push_back(selectedTask);
        }
      }

      render();
    } else {
      _task.concat(*key);
      _newKey = true;
      render();
    }
    if (selectedTaskIndex == 0 && tasks.size() == 0) {
      selectedTaskIndex = -1;
    }
  }
}

void Todo::addTask() {
  if (_task.length() > 0) {
    tasks.push_back(_task);
    _task = "";
  }
}