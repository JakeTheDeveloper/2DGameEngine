#pragma once
#include "glm/glm.hpp"
#include "Component.h"
#include "SDL.h"

struct CursorComponent: public Component  {
    const char* selectionFileName = "../assets/images/selection.png";
    glm::ivec2 position;
    SDL_Texture* texture;
    SDL_Rect srcRect = SDL_Rect{0,0,32,32};
    CursorComponent();
    ~CursorComponent();

    void Update(float deltaTime) override;
    void Render() override ;
};