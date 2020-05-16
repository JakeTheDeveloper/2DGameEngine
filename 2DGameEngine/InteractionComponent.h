#pragma once
#include "InteractionManager.h"
#include "Component.h"

struct InteractionComponent: public Component{
    InteractionManager* interactionManager;
    InteractionComponent(InteractionManager& interactionManager);
    void Interact();
    void Update(float deltaTime) override;
    void Render() override;
};