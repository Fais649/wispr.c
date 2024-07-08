#include "Todo.h"
#include "todo.h"
#include <Preferences.h>

Preferences savedTodos;

float inputHeight = Layout::window_content_height_abs * 0.08;

void Todo::save() {
  savedTodos.begin("saved_todos");
  int itemCount = tasks.size();

  savedTodos.putInt("item_count", itemCount);
  for (size_t i = 0; i < itemCount; i++) {
    if (tasks[i].length() > 0) {
      savedTodos.putString("todo_item_" + i, tasks[i]);
    }
  }
  saveLastInputs();
  savedTodos.end();
}

void Todo::saveLastInputs() {
  savedTodos.begin("saved_todos");
  if (_task.length() > 0) {
    savedTodos.putString("last_inputs", _task);
  } else {
    savedTodos.putString("last_inputs", "");
  }
  savedTodos.end();
}

void Todo::load() {
  savedTodos.begin("saved_todos");
  int itemCount = savedTodos.getInt("item_count");
  String lastInputs = savedTodos.getString("last_inputs", "");
  savedTodos.end();

  savedTodos.begin("saved_todos");
  for (size_t i = 0; i < itemCount; i++) {
    String item = savedTodos.getString("todo_item_" + i);

    if (item.length() > 0) {
      tasks.push_back(item);
    }
  }
  savedTodos.end();

  if (lastInputs.length() > 0) {
    _task = lastInputs;
  }
}

void Todo::render() {
  Serial.println("TODO RENDER");
  display.setWindow(Layout::window_x_abs, Layout::window_y_abs,
                    Layout::window_width_abs, Layout::window_height_abs);

  if (_newKey) {
    drawText();
    saveLastInputs();
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
  display.setWindow(Layout::window_content_x_abs,
                    Layout::window_content_y_abs +
                        Layout::window_content_height_abs - inputHeight,
                    Layout::window_content_width_abs, inputHeight);

  //display.setTextSize(4);
  display.setTextColor(TFT_WHITE);
  display.fillRect(Layout::window_content_x_abs,
                   Layout::window_content_y_abs +
                       Layout::window_content_height_abs - inputHeight,
                   Layout::window_content_width_abs, inputHeight, TFT_BLACK);

  display.drawString(_task, Layout::window_content_x_abs,
                     Layout::window_content_y_abs +
                         Layout::window_content_height_abs - inputHeight);
  display.display();
  _newKey = false;
}

void Todo::drawList() {
  display.setEpdMode(epd_fastest);
  drawWindow("todo;");
  for (size_t i = 0; i < tasks.size(); ++i) {
    String symbol = "[x]";
    String currentTask = tasks[i];
    display.setCursor(Layout::window_content_x_abs +
                          Layout::window_content_x_indent_abs,
                      (i * Layout::window_content_text_line_height_abs) +
                          Layout::window_content_y_abs +
                          Layout::window_content_title_height_abs);

    drawCursor(i, currentTask, symbol);
  }
}

void Todo::drawCursor(size_t i, String &currentTask, String &symbol) {
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
    } else if (keyIn == 0xD &&
               tasks.size() < Layout::window_content_text_lines) {
      addTask();
      _newEnter = true;
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
    } else if (keyIn == 0x7F) {
      if (selectedTaskIndex != -1) {
        tasks.erase(tasks.begin() + selectedTaskIndex);
      }
    } else if (keyIn == 0x09) {
      if (selectedTaskIndex != -1) {
        String selectedTask = tasks[selectedTaskIndex];
        if (selectedTask.charAt(0) != '%') {
          tasks[selectedTaskIndex] = "%" + selectedTask;
        } else {
          tasks[selectedTaskIndex] = selectedTask.substring(1);
        }
      }
    } else {
      Serial.println("addKey");
      _task.concat(*key);
      _newKey = true;
    }
    render();
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