#include "TransformComponent.h"
#include <iostream>
TransformComponent::TransformComponent(glm::vec2 position, glm::vec2 velocity, uint32_t w, uint32_t h, int scale)
	: position(position), velocity(velocity), width(w), height(h), scale(scale) {

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

	if (direction.x > 0) {
		facingDirection = (FacingDirection::FACING_RIGHT);
	}

	facingDirection = FacingDirection::FACING_NONE;

	if (direction.x < 0) {
		facingDirection = FacingDirection::FACING_LEFT;
	}
	else if(direction.x > 0) {
		facingDirection = FacingDirection::FACING_RIGHT;
	}

	if (direction.y > 0) {
		facingDirection = FacingDirection::FACING_DOWN;
	}
	else if (direction.y < 0) {
		facingDirection = FacingDirection::FACING_UP;
	}
}

void TransformComponent::Render() {

}