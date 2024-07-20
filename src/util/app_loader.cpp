#include "app_loader.h"
#include "note.h"
#include "todo.h"

Application *AppLoader::loadApp(AppName appName) {
  switch (appName) {
  case AppName::TODO:
    return new Todo();
    break;
  case AppName::NOTE:
    return new Note();
    break;
  default:
    break;
  }
  return new Todo();
}
