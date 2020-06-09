#pragma once
#include "glm/glm.hpp"
#include "Component.h"
#include "SDL.h"

struct CursorComponent: public Component  {
    glm::ivec2 position;
    SDL_Rect srcRect = SDL_Rect{0,0,32,32};
    CursorComponent() = default;
    ~CursorComponent() = default;

    void Update(float deltaTime) override;
    void Render() override ;
};