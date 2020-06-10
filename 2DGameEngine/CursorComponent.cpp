#include "CursorComponent.h"
#include "TextureManager.h"
#include "SpriteComponent.h"
#include "SDL.h"
#include <iostream>

void CursorComponent::Update(float deltaTime) {

}

void CursorComponent::Render() {
    SDL_GetMouseState(&position.x, &position.y);
    int drawPositionX = ((int)((position.x) / TILESIZE)) * TILESIZE;
    int drawPositionY = ((int)((position.y) / TILESIZE)) * TILESIZE;

    auto dstRect = SDL_Rect{
        drawPositionX,
        drawPositionY,
        TILESIZE, TILESIZE};

    owner->GetComponent<TransformComponent>()->position.x = position.x + Game::camera.x;
    owner->GetComponent<TransformComponent>()->position.y = position.y + Game::camera.y;

    TextureManager::Draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
}

CursorComponent::~CursorComponent() {
    if(texture != nullptr){
        delete texture;
    }
}

CursorComponent::CursorComponent() {
    texture = TextureManager::LoadTexture(selectionFileName);
}
