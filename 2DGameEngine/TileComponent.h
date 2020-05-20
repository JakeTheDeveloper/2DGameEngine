#pragma once
#include <SDL.h>
#include "../extern/glm/glm.hpp"
#include "EntityManager.h"
#include "TextureManager.h"

struct TileComponent: public Component {
public:
	SDL_Texture* texture;
	SDL_Rect srcRect; // source rectangle pointing at the png/spritesheet
	SDL_Rect dstRect; // destination rectangle pointing at Game Window for drawing
	glm::vec2 position;

	TileComponent(uint32_t srcRectX, uint32_t srcRectY, uint32_t x, uint32_t  y, uint32_t tileSize, int tileScale, std::string assetTextureId);
	~TileComponent();
	void Update(float deltaTime) override;
	void Render() override;
}; 