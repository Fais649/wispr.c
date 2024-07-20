#include "todo.h"
#include <Preferences.h>

Preferences savedTodos;

String Todo::getAppTitle() { return "todo;"; }

void Todo::save() {
  JsonDocument todoDoc;
  JsonObject root = todoDoc.to<JsonObject>();
  int itemCount = tasks.size();
  root["date"] = timeKeeper.getFormattedDate();
  root["item_count"] = itemCount;
  root["last_inputs"] = _task;
  JsonArray items = root["items"].to<JsonArray>();

  for (size_t i = 0; i < itemCount; i++) {
    if (tasks[i].length() > 0) {
      items.add(tasks[i]);
    }
  }

  String fileName = root["date"];
  String serializedData;
  serializeJson(root, serializedData);

  savedTodos.begin("saved_todos");
  savedTodos.putString(fileName.c_str(), serializedData);
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
  int itemCount = savedTodos.getInt("item_count");

  savedTodos.begin("saved_todos");
  String lastInputs = savedTodos.getString("last_inputs", "");
  String items = savedTodos.getString(timeKeeper.getFormattedTime().c_str());
  savedTodos.end();

  JsonDocument todoData;
  deserializeJson(todoData, items.c_str());

  for (size_t i = 0; i < itemCount; i++) {
    String item = todoData["items"][i];
    if (item.length() > 0) {
      tasks.push_back(item);
    }
  }

  if (lastInputs.length() > 0) {
    _task = lastInputs;
  }
}

void Todo::render(bool fullRender) {
  Serial.println("TODO RENDER");
  if (fullRender) {
    drawList();
    drawText();
    display.display();
    return;
  }

  if (_newKey) {
    drawText();
    saveLastInputs();
  } else {
    display.updateWindow();
    drawList();
  }

  display.display();
  save();
}

void Todo::drawText(int textColor) {
  Serial.println("TEXT RENDER");
  Serial.println(_task);

  display.setTextColor(textColor);
  display.drawString(_task, Layout::window_content_x_abs,
                     Layout::window_content_y_abs +
                         Layout::window_content_height_abs - Layout::window_input_height_abs);
  _newKey = false;
}

void Todo::drawList() {
  for (size_t i = 0; i < tasks.size(); ++i) {
    String currentTask = tasks[i];
    display.setCursor(Layout::window_content_x_abs +
                          Layout::window_content_x_indent_abs,
                      (i * Layout::window_content_text_line_height_abs) +
                          Layout::window_content_y_abs +
                          Layout::window_content_title_height_abs);

    drawCursor(i, currentTask);
  }
}

void Todo::drawCursor(size_t i, String &currentTask) {
  bool isSelected = (i == selectedTaskIndex);
  bool isCompleted = (currentTask.charAt(0) == '%');

  Serial.println("drawing list cursor");

  if (isCompleted) {
    currentTask = currentTask.substring(1);
  }

  display.setTextColor(isSelected ? TFT_WHITE
                                  : (isCompleted ? TFT_WHITE : TFT_WHITE));
  if (isSelected) {
    display.setFont(Layout::dock_symbol_font);
    display.setTextSize(1.5);
    display.print(Layout::finger_icon);
  }
  display.setFont(nullptr);
  display.setTextSize(Layout::window_content_text_size);
  display.printf("%s\n", currentTask.c_str());
}

void Todo::handleKeyPress(const char *key) {
  if (key != nullptr) {
    char keyIn = *key;
    Serial.println("todoKey");
    Serial.println(_task);
    Serial.print("Key pressed: ");
    Serial.println(*key, HEX);

    switch (keyIn) {
    case 8: // Backspace
      if (_task.length() > 0) {
        drawText(TFT_BLACK);
        _task.remove(_task.length() - 1);
        _newKey = true;
      }
      break;
    case 0xD: // Enter
      if (tasks.size() < Layout::window_content_text_lines) {
        addTask();
        _newEnter = true;
      }
      break;
    case 0xB5: // Up arrow
    case 0xB6: // Down arrow
      handleNavigationKeys(keyIn);
      break;
    case 0x7F: // Delete
      if (selectedTaskIndex != -1) {
        tasks.erase(tasks.begin() + selectedTaskIndex);
      }
      break;
    case 0x09: // Tab
      if (selectedTaskIndex != -1) {
        String &selectedTask = tasks[selectedTaskIndex];
        selectedTask = (selectedTask.charAt(0) == '%')
                           ? selectedTask.substring(1)
                           : "%" + selectedTask;
      }
      break;
    default:
      handleCharacterKey(keyIn);
      break;
    }
    render();
    if (selectedTaskIndex == 0 && tasks.empty()) {
      selectedTaskIndex = -1;
    }
  }
}

void Todo::handleNavigationKeys(char keyIn) {
  if (tasks.empty()) {
    selectedTaskIndex = -1;
  } else if (keyIn == 0xB5 && selectedTaskIndex == -1) {
    selectedTaskIndex = tasks.size();
  } else if (keyIn == 0xB5 && selectedTaskIndex > -1) {
    selectedTaskIndex--;
  } else if (keyIn == 0xB6 && selectedTaskIndex < tasks.size() - 1) {
    selectedTaskIndex++;
  } else if (keyIn == 0xB6 && selectedTaskIndex == -1) {
    selectedTaskIndex = 0;
  }
}

void Todo::handleSpecialKeys(char keyIn) {
  // Handle other special keys if needed
}

void Todo::handleCharacterKey(char keyIn) {
  Serial.println("addKey");
  _task.concat(keyIn);
  _newKey = true;
}

void Todo::addTask() {
  if (_task.length() > 0) {
    tasks.push_back(_task);
    drawText(TFT_BLACK);
    _task = "";
  }
}
