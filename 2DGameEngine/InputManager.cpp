#include "InputManager.h"

InputManager::~InputManager() {

}

void InputManager::GetInputEvents() {
    ClearEventQueue();
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_QUIT:
                Game::isRunning = false;
                break;
            default:
                eventQueue.push_back(new SDL_Event(sdlEvent));
                break;
        }
    }
}


void InputManager::ClearEventQueue() {
    if(eventQueue.size() > 0){
        for(auto e: eventQueue)
            delete e;
        eventQueue.clear();
    }
}