#include "KeyboardControlComponent.h"
#include <iostream>
KeyboardControlComponent::KeyboardControlComponent() {
	
}

void KeyboardControlComponent::Initialize() {

}

void KeyboardControlComponent::Update(float deltaTime) {
    if(ownerTransform != nullptr){
        ownerTransform->velocity.x += _xVel * deltaTime;
        ownerTransform->velocity.y += _yVel * deltaTime;
    }
}

void KeyboardControlComponent::Render() {

}

void KeyboardControlComponent::HandleInput(SDL_Event event) {
    switch(event.type){
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        ownerTransform->velocity.y = -10;
                        break;
                    case SDLK_a:
                        ownerTransform->velocity.x = -10;
                        break;
                    case SDLK_s:
                        ownerTransform->velocity.y = 10;
                        break;
                    case SDLK_d:
                        ownerTransform->velocity.x = 10;
                        break;
                    case SDLK_e:

                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                    case SDLK_s:
                        ownerTransform->velocity.y = 0;
                        break;
                    case SDLK_a:
                    case SDLK_d:
                        ownerTransform->velocity.x = 0;
                        break;
                }
            break;
    }
}
