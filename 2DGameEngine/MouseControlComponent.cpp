#include <math.h>
#include "MouseControlComponent.h"
#include <iostream>
#include "TileComponent.h"
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
    auto cursor = Game::manager.GetEntityByName("cursor");
    auto tileX = static_cast<int>(cursor.GetComponent<TransformComponent>()->position.x / (TILE_SIZE * MAP_SCALE));
    auto tileY = static_cast<int>(cursor.GetComponent<TransformComponent>()->position.y / (TILE_SIZE * MAP_SCALE));
    auto tilePos = Game::worldManager->tiles[tileX][tileY]->GetComponent<TileComponent>()->position;
    dst = new glm::vec2(tilePos.x, tilePos.y);
    isMoving = false;
    start = nullptr;
}