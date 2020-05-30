#pragma once
#include "TransformComponent.h"
struct MouseControlComponent : public Component {
    TransformComponent ownerTransform;
    glm::vec2* start = nullptr;
    glm::vec2* dst = nullptr;
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;
};