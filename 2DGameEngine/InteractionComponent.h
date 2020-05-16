#pragma once
#include "InteractionManager.h"
#include "Component.h"

struct InteractionManager;

struct InteractionComponent: public Component{
    InteractionComponent(InteractionManager& interactionManager);
    InteractionManager& interactionManager;
    void Interact();
    void Update(float deltaTime) override;
    void Render() override;
    void Initialize() override;
};