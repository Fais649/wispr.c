#ifndef STORAGE_MANAGER_H
#define STORAGE_MANAGER_H

#include "global_includes.h"

class StorageManager {
public:
  void saveData(const String &key, const String &data);
  String loadData(const String &key);
};

#endif