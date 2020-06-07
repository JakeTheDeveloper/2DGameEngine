#pragma once
#include "TransformComponent.h"
#include "EntityManager.h"
struct MouseControlComponent : public Component {
    MouseControlComponent() = default;
    bool isMoving = false;
    float distance;
    glm::vec2 direction;
    TransformComponent* ownerTransform{};
    glm::vec2* start = nullptr;
    glm::vec2* dst = nullptr;
    ~MouseControlComponent() override;
    void HandleMouseInput(SDL_Event event);
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;
};