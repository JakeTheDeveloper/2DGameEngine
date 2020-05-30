#include <math.h>
#include "MouseControlComponent.h"
#include <iostream>
void MouseControlComponent::Initialize() {

}

void MouseControlComponent::Update(float deltaTime) {
    if(dst != nullptr && start != nullptr){
        auto directionVecX = dst->x - start->x;
        auto directionVecY = dst->y - start->y;
        auto vecMag = sqrt((pow((dst->x - start->x), 2), pow(dst->y - start->y, 2)));
        auto normalizedVec = glm::vec2(directionVecX / vecMag, directionVecY / vecMag);
        std::cout << normalizedVec.x << " " << normalizedVec.y << std::endl;
    }
}

void MouseControlComponent::Render() {

}

MouseControlComponent::MouseControlComponent() {

}

MouseControlComponent::~MouseControlComponent() {
    if(start != nullptr)
        delete start;
    if(dst != nullptr)
        delete dst;
}
