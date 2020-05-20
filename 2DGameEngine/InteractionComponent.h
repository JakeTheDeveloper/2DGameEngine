#pragma once
#include "InteractionManager.h"
#include "TransformComponent.h"

struct InteractionManager;

struct InteractionComponent: public Component{
    InteractionComponent(InteractionManager& interactionManager);
    InteractionManager& interactionManager;
    void Interact();
    void Update(float deltaTime) override;
    void Render() override;
    void Initialize() override;

private:
    bool Interactable(TransformComponent src, TransformComponent targ);
};