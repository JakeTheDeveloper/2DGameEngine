#include "TransformComponent.h"

TransformComponent::TransformComponent(glm::vec2 position, glm::vec2 velocity, uint32_t w, uint32_t h, int scale)
	: position(position), velocity(velocity), width(w), height(h), scale(scale) {

}

void TransformComponent::Initialize() {

}

void TransformComponent::Update(float deltaTime) {
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
}

void TransformComponent::Render() {

}