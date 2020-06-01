#include <math.h>
#include "MouseControlComponent.h"
#include <iostream>
void MouseControlComponent::Initialize() {
    ownerTransform = owner->GetComponent<TransformComponent>();
}

void MouseControlComponent::Update(float deltaTime) {
    if(dst != nullptr && start != nullptr){
        auto directionVecX = dst->x - start->x;
        auto directionVecY = dst->y - start->y;
        auto vecMag = sqrt((pow((directionVecX), 2) + pow(directionVecY, 2)));
        auto normalizedVec = glm::vec2(directionVecX / vecMag, directionVecY / vecMag);
        ownerTransform->position += ((normalizedVec * glm::vec2(90)) * deltaTime);

        if(start->x - ownerTransform->position.x >= (dst->x - start->x) && start->y - ownerTransform->position.y >= (dst->y - start->y)){
            ownerTransform->position = *dst;
            dst = nullptr;
            start = nullptr;
        }
    }
}

void MouseControlComponent::Render() {

}

MouseControlComponent::MouseControlComponent() = default;

MouseControlComponent::~MouseControlComponent() {
    if(start != nullptr)
        delete start;
    if(dst != nullptr)
        delete dst;
}
