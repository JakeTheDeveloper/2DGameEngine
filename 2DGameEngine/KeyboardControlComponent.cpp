#include "KeyboardControlComponent.h"
#include <iostream>
KeyboardControlComponent::KeyboardControlComponent() {
	
}

void KeyboardControlComponent::Initialize() {
	ownerTransform = owner->GetComponent<TransformComponent>();
	sprite = owner->GetComponent<SpriteComponent>();
}

void KeyboardControlComponent::Update(float deltaTime) {
	if (_xVel == 0) {
		ownerTransform->velocity.x = 0;
	}

	if (_yVel == 0) {
		ownerTransform->velocity.y = 0;
	}

	if (ownerTransform->velocity.x > 15.f) {
		ownerTransform->velocity.x = 15.f;
	}
	else if(ownerTransform->velocity.x < -15.f){
		ownerTransform->velocity.x = -15.f;
	}

	if (ownerTransform->velocity.y > 15.f) {
		ownerTransform->velocity.y = 15.f;
	}
	else if (ownerTransform->velocity.y < -15.f) {
		ownerTransform->velocity.y = -15.f;
	}

	ownerTransform->velocity.x += _xVel * deltaTime;
	ownerTransform->velocity.y += _yVel * deltaTime;
}

void KeyboardControlComponent::Render() {

}

void KeyboardControlComponent::SetMouseDestination() {
    if(owner->HasComponent<MouseControlComponent>()){
        auto x = 0;
        auto y = 0;
        auto mcc = owner ->GetComponent<MouseControlComponent>();
        SDL_GetMouseState(&x, &y);
        mcc->dst = new glm::vec2(x, y);
        mcc->start = &ownerTransform->position;
        Game::mousePos.x = x;
        Game::mousePos.y = y;
    }
}
