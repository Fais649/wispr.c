#include "note.h"
#include <Preferences.h>

Preferences savedNotes;
String Note::getAppTitle() { return "note;"; }

void Note::save() {
  savedNotes.begin("saved_notes");
  int itemCount = tasks.size();

  savedNotes.putInt("item_count", itemCount);
  for (size_t i = 0; i < itemCount; i++) {
    if (tasks[i].length() > 0) {
      savedNotes.putString("note_item_" + i, tasks[i]);
    }
  }
  savedNotes.end();
}

void Note::load() {
  savedNotes.begin("saved_notes");
  int itemCount = savedNotes.getInt("item_count");
  for (size_t i = 0; i < itemCount; i++) {
    String item = savedNotes.getString("note_item_" + i);

    if (item.length() > 0) {
      tasks.push_back(item);
    }
  }
  savedNotes.end();
}

void Note::render(bool fullRender) {
  Serial.println("NOTE RENDER");
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

void Note::drawText() {
  display.setEpdMode(Layout::display_mode_fastest);
  Serial.println("TEXT RENDER");
  Serial.println(_task);
  // display.setTextSize(4);
  display.setTextColor(TFT_WHITE);
  display.fillRect(Layout::window_x_abs + 2 * Layout::window_hor_margin,
                   Layout::window_y_abs + Layout::window_height_abs -
                       inputHeight - 2 * Layout::window_ver_margin,
                   Layout::window_width_abs - 4 * Layout::window_hor_margin,
                   inputHeight, TFT_BLACK);
  display.drawString(_task,
                     Layout::window_x_abs + 2 * Layout::window_hor_margin,
                     Layout::window_y_abs + Layout::window_height_abs -
                         inputHeight - 2 * Layout::window_ver_margin);
  display.display();
  _newKey = false;
}

void Note::drawList() {
  display.setEpdMode(Layout::display_mode_fastest);
  display.fillRoundRect(Layout::window_x_abs - Layout::window_hor_margin / 3,
                        Layout::window_y_abs + Layout::window_ver_margin / 3,
                        Layout::window_width_abs, Layout::window_height_abs, 25,
                        TFT_DARKGRAY);
  display.fillRoundRect(Layout::window_x_abs, Layout::window_y_abs,
                        Layout::window_width_abs, Layout::window_height_abs, 25,
                        TFT_WHITE);
  display.fillRoundRect(
      Layout::window_x_abs + Layout::window_hor_margin,
      Layout::window_y_abs + Layout::window_ver_margin,
      Layout::window_width_abs - (2 * Layout::window_hor_margin),
      Layout::window_height_abs - (2 * Layout::window_ver_margin), 15,
      TFT_BLACK);

  // display.setTextSize(5);
  display.setCursor(Layout::window_x_abs + 35, Layout::window_y_abs + 35);
  display.setTextColor(TFT_WHITE);

  display.print("note;");

  // display.setTextSize(3);
  for (size_t i = 0; i < tasks.size(); ++i) {
    display.setCursor(Layout::window_x_abs + 35,
                      (i + 1.2) * Layout::window_y_abs + 100);
    if (i == selectedTaskIndex) {
      display.setTextColor(TFT_DARKGREY, TFT_BLACK);
    } else {
      display.setTextColor(TFT_WHITE);
    }
    display.printf("[%d] - %s\n", i + 1, tasks[i].c_str());
  }
}

void Note::handleKeyPress(const char *key) {
  if (key != nullptr) {
    char keyIn = *key;
    Serial.println("noteKey");
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
    } else {
      _task.concat(*key);
      _newKey = true;
      render();
    }
  }
}

void Note::addTask() {
  if (_task.length() > 0) {
    tasks.push_back(_task);
    _task = "";
  }
}
