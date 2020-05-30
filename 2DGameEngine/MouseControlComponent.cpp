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
        // divide x and y  by mag for normalized vec
        auto normalizedVec =
    }
}

void MouseControlComponent::Render() {

}
