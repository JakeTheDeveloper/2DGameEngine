#include <math.h>
#include "MouseControlComponent.h"
#include <iostream>
#include "Game.h"

void MouseControlComponent::Initialize() {
    ownerTransform = owner->GetComponent<TransformComponent>();
}

void MouseControlComponent::Update(float deltaTime) {
    if(dst != nullptr){
        if(start == nullptr) {
            start = new glm::vec2(ownerTransform->position);
        }

        if(!isMoving) {
            isMoving = true;
            distance = glm::distance(*start, *dst);
            direction = glm::normalize(*dst - *start);
            ownerTransform->position = *start;
        }

        if(isMoving){
            ownerTransform->position += direction * 150.f * deltaTime;
            std::cout << start->x << std::endl;
            if(glm::distance(*start, ownerTransform->position) >= distance){
                ownerTransform->position = *dst;
                dst = nullptr;
                start = nullptr;
                isMoving = false;
            }
        }
    }
}

void MouseControlComponent::Render() {

}

MouseControlComponent::~MouseControlComponent() {
    if(start != nullptr)
        delete start;
    if(dst != nullptr)
        delete dst;
}

void MouseControlComponent::HandleMouseInput(SDL_Event event) {
    dst = new glm::vec2(Game::mousePos.x, Game::mousePos.y);
    isMoving = false;
    start = nullptr;
}