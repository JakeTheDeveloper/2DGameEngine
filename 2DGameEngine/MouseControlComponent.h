#pragma once
#include "TransformComponent.h"
#include "EntityManager.h"
struct MouseControlComponent : public Component {
    MouseControlComponent();
    TransformComponent* ownerTransform;
    glm::vec2* start = nullptr;
    glm::vec2* dst = nullptr;
    ~MouseControlComponent();
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;
};