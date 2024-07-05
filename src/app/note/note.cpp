#include "Note.h"
#include <Preferences.h>

Preferences savedNotes;

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

void Note::render() {
  Serial.println("NOTE RENDER");
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

void Note::drawText() {
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

void Note::drawList() {
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

  display.print("note;");

  display.setTextSize(3);
  for (size_t i = 0; i < tasks.size(); ++i) {
    display.setCursor(rectX + 35, (i + 1.2) * rectY + 100);
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