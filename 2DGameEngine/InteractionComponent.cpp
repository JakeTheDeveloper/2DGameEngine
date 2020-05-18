#include "InteractionComponent.h"
#include <iostream>

InteractionComponent::InteractionComponent(InteractionManager& interactionManager) : interactionManager(interactionManager) {

}

void InteractionComponent::Interact() {
    auto ownerTransform = owner->GetComponent<TransformComponent>();
    auto xDiff = 0.f;
    auto yDiff = 0.f;

    for (auto& e : owner->manager.interactableEntities) {
        if (e->Name.compare(owner->Name) != 0) {
            auto eTrans = e->GetComponent<TransformComponent>();
            auto trans = ownerTransform->position - eTrans->position;
            //std::cout << trans.x << " " << trans.y << std::endl;

            interactionManager.interactionQueue.emplace_back(new InteractionEvent{*owner, *e, PLAYER_TO_OBJECT});
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
