#ifndef APPLOADER_H
#define APPLOADER_H

#include "global_includes.h"

class AppLoader {
public:
  Application *loadApp(AppName appName);
};
#endif