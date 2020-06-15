#include "TileComponent.h"
#include "Game.h"

TileComponent::TileComponent(uint32_t srcRectX, uint32_t srcRectY, uint32_t x, uint32_t  y, uint32_t tileSize, int tileScale, std::string assetTextureId) {
	texture = Game::assetManager->GetTexture(assetTextureId);
	// srcRect is from the tilemap.png
	srcRect.x = srcRectX;
	srcRect.y = srcRectY;
	srcRect.w = tileSize;
	srcRect.h = tileSize;

	// dstRect is where we want to render the tile in the gameworld
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = tileSize * tileScale;
	dstRect.h = tileSize * tileScale;

	position.x = x;
	position.y = y;
}

TileComponent::~TileComponent() {
	SDL_DestroyTexture(texture);
}

void TileComponent::Update(float deltaTime) {
	dstRect.x = position.x - Game::camera.x;
	dstRect.y = position.y - Game::camera.y;
}

void TileComponent::Render() {
	TextureManager::Draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
}

void TileComponent::DrawHighlight(SDL_Texture& highlightTexture, SDL_Rect srcRect) {
    TextureManager::Draw(&highlightTexture, srcRect, dstRect, SDL_FLIP_NONE);
}
