#include <math.h>
#include "MouseControlComponent.h"

void MouseControlComponent::Initialize() {

}

void MouseControlComponent::Update(float deltaTime) {
    if(dst != nullptr && start != nullptr){
        auto normalizedVec = sqrt((pow((dst->x - start->x), 2), pow(dst->y - start->y, 2)));

    }
}

void MouseControlComponent::Render() {

}
