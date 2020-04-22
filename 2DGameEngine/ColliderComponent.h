#pragma once
#include "Game.h"
#include "TransformComponent.h"
#include "EntityManager.h"

class ColliderComponent: public Component {
public:
	std::string colliderTag;
	SDL_Rect collider;
	SDL_Rect srcRect;
	SDL_Rect dstRect;
	TransformComponent* transform;

	ColliderComponent(std::string tag, int posX, int posY, int width, int height);
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
};