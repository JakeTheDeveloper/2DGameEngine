#include "CursorComponent.h"
#include "TextureManager.h"
#include "SpriteComponent.h"
#include "SDL.h"
void CursorComponent::Update(float deltaTime) {
    owner->GetComponent<TransformComponent>()->position.x = position.x;
    owner->GetComponent<TransformComponent>()->position.y = position.y;
}

void CursorComponent::Render() {
    SDL_GetMouseState(&position.x, &position.y);
    int drawPositionX = ((int)(position.x / TILESIZE)) * TILESIZE;
    int drawPositionY = ((int)(position.y / TILESIZE)) * TILESIZE;

    auto dstRect = SDL_Rect{
        drawPositionX,
        drawPositionY,
        TILESIZE, TILESIZE};

    TextureManager::Draw(owner->GetComponent<SpriteComponent>()->texture, srcRect, dstRect, SDL_FLIP_NONE);
}
