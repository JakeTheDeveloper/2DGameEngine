#include "KeyboardControlComponent.h"
#include <iostream>
KeyboardControlComponent::KeyboardControlComponent(int movementSpeed) : movementSpeed(movementSpeed) {
	
}

void KeyboardControlComponent::Initialize() {

}

void KeyboardControlComponent::Update(float deltaTime) {
    auto ownerTransform = owner->GetComponent<TransformComponent>();
    ownerTransform->velocity.x += _xVel * deltaTime;
    ownerTransform->velocity.y += _yVel * deltaTime;
}

void KeyboardControlComponent::Render() {

}

void KeyboardControlComponent::HandleInput(SDL_Event event) {
    auto ownerTransform = owner->GetComponent<TransformComponent>();
    switch(event.type){
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        ownerTransform->velocity.y = -movementSpeed;
                        break;
                    case SDLK_a:
                        ownerTransform->velocity.x = -movementSpeed;
                        break;
                    case SDLK_s:
                        ownerTransform->velocity.y = movementSpeed;
                        break;
                    case SDLK_d:
                        ownerTransform->velocity.x = movementSpeed;
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
