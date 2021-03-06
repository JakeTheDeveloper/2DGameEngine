#include <math.h>
#include "MouseControlComponent.h"
#include <iostream>
#include "TileComponent.h"
#include "Game.h"

void MouseControlComponent::Initialize() {

}

void MouseControlComponent::Update(float deltaTime) {
    if(dst != nullptr){
        if(start == nullptr) {
            start = new glm::vec2(owner->GetComponent<TransformComponent>()->position.x, owner->GetComponent<TransformComponent>()->position.y);
        }

        if(!isMoving) {
            isMoving = true;
            distance = glm::distance(*start, *dst);
            direction = glm::normalize(*dst - *start);
//            owner->GetComponent<TransformComponent>()->position = *start;
        }

        if(isMoving){
            auto& ownerPosition = owner->GetComponent<TransformComponent>()->position;
            ownerPosition += direction * 150.f * deltaTime;
            if(glm::distance(*start, ownerPosition) >= distance){
                ownerPosition = *dst;
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

    if(tileX < 0){
        tileX = 0;
    } else {
        tileX = tileX > MAP_SIZE_X - 1 ? MAP_SIZE_X : tileX;
    }

    if(tileY < 0){
        tileY = 0;
    }else{
        tileY = tileY > MAP_SIZE_Y - 1 ? MAP_SIZE_Y : tileY;
    }

    auto tilePos = Game::worldManager->tiles[tileX][tileY]->GetComponent<TileComponent>()->position;
    dst = new glm::vec2(tilePos.x, tilePos.y);
    isMoving = false;
    start = nullptr;
}