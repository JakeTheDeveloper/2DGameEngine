#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(std::string tag, int posX, int posY, int width, int height)
	: colliderTag(tag) {
	this->collider = { posX, posY, width, height };
}

void ColliderComponent::Initialize() {
	if (owner->HasComponent<TransformComponent>()) {
		transform = owner->GetComponent<TransformComponent>();
		srcRect = { 0, 0, static_cast<int>(transform->width), static_cast<int>(transform->height) };
		dstRect = { collider.x, collider.y, collider.w, collider.h };
	}
}

void ColliderComponent::Update(float deltaTime) {
	collider.x = static_cast<int>(transform->position.x);
	collider.y = static_cast<int>(transform->position.y);
	collider.w = transform->width * transform->scale;
	collider.h = transform->height * transform->scale;
	dstRect.x = collider.x - Game::camera.x;
	dstRect.y = collider.y - Game::camera.y;
}

void ColliderComponent::Render() {
	auto texture = Game::assetManager->GetTexture(COLLISION_TEXTURE_ID);
	auto transform = owner->GetComponent<TransformComponent>();
	SDL_Rect srcRect = {0, 0, 32, 32}; // start at beginning of file, 32x32;
	
	SDL_Rect dstRect = { 
		static_cast<int>(transform->position.x - Game::camera.x),
		static_cast<int>(transform->position.y - Game::camera.y),
		32, 32 };
	TextureManager::Draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
}