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