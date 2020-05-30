#pragma once
#include "TransformComponent.h"
struct MouseControlComponent : public Component {
    MouseControlComponent();
    glm::vec2* start = nullptr;
    glm::vec2* dst = nullptr;
    ~MouseControlComponent();
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;
};