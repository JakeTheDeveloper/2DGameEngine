#include "InteractionComponent.h"
#include <iostream>

InteractionComponent::InteractionComponent(InteractionManager& interactionManager) : interactionManager(interactionManager) {

}

void InteractionComponent::Interact() {
    for (auto& e : owner->manager.interactableEntities) {
        if (e->Name.compare(owner->Name) != 0) {
            if (owner->GetComponent<TransformComponent>(), e->GetComponent<TransformComponent>()) {
                interactionManager.interactionQueue.emplace_back(new InteractionEvent{*owner, *e, PLAYER_TO_OBJECT});
            }
        }
    }
}

bool InteractionComponent::Interactable(TransformComponent src, TransformComponent targ) {
    switch (owner->facingDirection) {
        case FacingDirection::FACING_LEFT:
            if (src.topLeft > targ.topRight) {

            }
            break;
        case FacingDirection::FACING_UP:

            break;
        case FacingDirection::FACING_RIGHT:

            break;
        case FacingDirection::FACING_DOWN:

            break;
    };
    return false;
}

void InteractionComponent::Update(float deltaTime){

}

void InteractionComponent::Render(){

}

void InteractionComponent::Initialize()
{
}
