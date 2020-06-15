#include "CursorComponent.h"
#include "TextureManager.h"
#include "SDL.h"
#include <iostream>
#include "TileComponent.h"

void CursorComponent::Update(float deltaTime) {

}

void CursorComponent::Render() {
    SDL_GetMouseState(&position.x, &position.y);

    int tileX = ((int)((position.x + Game::camera.x) / (TILE_SIZE * MAP_SCALE)));
    int tileY = ((int)((position.y + Game::camera.y) / (TILE_SIZE * MAP_SCALE)));

    Game::worldManager->tiles[tileX][tileY]->GetComponent<TileComponent>()->DrawHighlight(*texture, srcRect);

    owner->GetComponent<TransformComponent>()->position.x = position.x + Game::camera.x;
    owner->GetComponent<TransformComponent>()->position.y = position.y + Game::camera.y;
}

CursorComponent::~CursorComponent() {
    if(texture != nullptr){
        delete texture;
    }
}

CursorComponent::CursorComponent() {
    texture = TextureManager::LoadTexture(selectionFileName);
}
