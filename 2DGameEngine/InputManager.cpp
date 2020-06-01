#include "InputManager.h"

InputManager::~InputManager() {

}

void InputManager::GetInputEvents() {
    switch (sdlEvent.type) {
        case SDL_KEYDOWN:
            switch (sdlEvent.key.keysym.sym) {
                case SDLK_w:
                    _yVel = -10.f;
                    owner->facingDirection = FacingDirection::FACING_UP;
                    break;
                case SDLK_a:
                    _xVel = -10.f;
                    owner->facingDirection = FacingDirection::FACING_LEFT;
                    break;
                case SDLK_s:
                    _yVel = 10.f;
                    owner->facingDirection = FacingDirection::FACING_DOWN;
                    break;
                case SDLK_d:
                    _xVel = 10.f;
                    owner->facingDirection = FacingDirection::FACING_RIGHT;
                    break;
                case SDLK_e:
                    owner->GetComponent<InteractionComponent>()->Interact();
                    break;
                default:
                    break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            SetMouseDestination();
            break;
        case SDL_KEYUP:
            switch (sdlEvent.key.keysym.sym) {
                case SDLK_w:
                    if (_yVel < 0)
                        _yVel = 0;
                    break;
                case SDLK_a:
                    if (_xVel < 0)
                        _xVel = 0;
                    break;
                case SDLK_s:
                    if (_yVel > 0)
                        _yVel = 0;
                    break;
                case SDLK_d:
                    if (_xVel > 0)
                        _xVel = 0;
                    break;
            }
            break;
        default:
            break;
    }
}

void InputManager::ClearEventQueue() {
    if(!eventQueue.empty())
        for(auto& e: eventQueue)
            delete e;
}
