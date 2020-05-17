#include "InteractionComponent.h"

InteractionComponent::InteractionComponent(InteractionManager& interactionManager) : interactionManager(interactionManager) {

}

void InteractionComponent::Interact() {
    auto ownerTransform = owner->GetComponent<TransformComponent>();
    auto xDiff = 0.f;
    auto yDiff = 0.f;

    for (auto& e : owner->manager.interactableEntities) {
        auto eTrans = e->GetComponent<TransformComponent>();
        xDiff = ownerTransform->position.x - eTrans->position.x;
        yDiff = ownerTransform->position.y - eTrans->position.y;
        
        if ((xDiff < 6 && xDiff > -6) || (yDiff < 6 && yDiff > -6)){
            InteractionEvent ie = {
                *owner,
                *e,
                PLAYER_TO_OBJECT
            };
            interactionManager.interactionQueue.emplace_back(&ie);
        }
    }
}

void InteractionComponent::Update(float deltaTime){

}

void InteractionComponent::Render(){

}

void InteractionComponent::Initialize()
{
}
