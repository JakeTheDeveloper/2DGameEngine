#include "TransformComponent.h"
#include <iostream>
TransformComponent::TransformComponent(glm::vec2 position, glm::vec2 velocity, uint32_t w, uint32_t h, int scale)
	: position(position), velocity(velocity), width(w), height(h), scale(scale) {
	topLeft = position.x;
	topRight = position.x + w;
	botLeft = position.y + h;
	botRight = position.y + h + w;
}

void TransformComponent::Initialize() {

}

void TransformComponent::Update(float deltaTime) {
	position.x += velocity.x;
	position.y += velocity.y;
	
	if (velocity.x == 0 && velocity.y == 0) {
		return;
	}
	else {
		direction = velocity;
	}
}

void TransformComponent::Render() {

}
