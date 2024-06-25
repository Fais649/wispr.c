#include "app_loader.h"
#include "app/todo/todo.h"
#include "app/note/note.h"

Application *AppLoader::loadApp(AppName appName)
{
    switch (appName)
    {
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