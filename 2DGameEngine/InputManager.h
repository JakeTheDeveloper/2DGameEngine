#pragma once
#include "Game.h"

struct InputManager {
    std::vector<SDL_Event*> eventQueue;
    InputManager() = default;
    ~InputManager();
    void GetInputEvents();
    void ClearEventQueue();
};
