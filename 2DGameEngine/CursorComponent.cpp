#include "CursorComponent.h"
#include "TextureManager.h"
#include "SDL.h"
#include <iostream>
#include "TileComponent.h"
#include <iostream>

void CursorComponent::Update(float deltaTime) {

}

void CursorComponent::Render() {
    SDL_GetMouseState(&position.x, &position.y);
    auto cameraPosition = Game::manager.GetEntityByName("camera").GetComponent<TransformComponent>()->position;
    int tileX = ((int)((position.x + cameraPosition.x) / (TILE_SIZE * MAP_SCALE)));
    int tileY = ((int)((position.y + cameraPosition.y) / (TILE_SIZE * MAP_SCALE)));

    if(tileX < 0){
        tileX = 0;
    } else {
        tileX = tileX > MAP_SIZE_X - 1 ? MAP_SIZE_X : tileX;
    }

    if(tileY < 0){
        tileY = 0;
    }else{
        tileY = tileY > MAP_SIZE_Y - 1 ? MAP_SIZE_Y : tileY;
    }

    if(Game::worldManager->tiles[tileX][tileY] == nullptr){
        std::cout << tileY << std::endl;
    }

    Game::worldManager->tiles[tileX][tileY]->GetComponent<TileComponent>()->DrawHighlight(*texture, srcRect);

    owner->GetComponent<TransformComponent>()->position.x = position.x + cameraPosition.x;
    owner->GetComponent<TransformComponent>()->position.y = position.y + cameraPosition.y;
}

CursorComponent::~CursorComponent() {
    if(texture != nullptr){
        delete texture;
    }
}

CursorComponent::CursorComponent() {
    texture = TextureManager::LoadTexture(selectionFileName);
}