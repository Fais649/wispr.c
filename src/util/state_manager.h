#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "global_includes.h"

struct AppState {
    // Define the state properties here
};

class StateManager {
public:
    void saveState(Application* app);
    void loadState(Application* app);
private:
    std::map<Application*, AppState> stateMap;
};

#endif