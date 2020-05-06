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

void KeyboardControlComponent::HandleInput(SDL_Event& sdlEvent) {
	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		switch (sdlEvent.key.keysym.sym) {
		case SDLK_w:
			_yVel = -10.f;
			break;
		case SDLK_a:
			_xVel = -10.f;
			break;
		case SDLK_s:
			_yVel = 10.f;
			break;
		case SDLK_d:
			_xVel = 10.f;
			break;
		default:
			break;
		}
		break;

	case SDL_KEYUP:
		switch (sdlEvent.key.keysym.sym) {
		case SDLK_w:
			if (_yVel < 0)
				_yVel = 0;
			break;
		case SDLK_a:
			if (_xVel < 0)
				_xVel = 0;
			break;
		case SDLK_s:
			if (_yVel > 0)
				_yVel = 0;
			break;
		case SDLK_d:
			if (_xVel > 0)
				_xVel = 0;
			break;
		}
		break;

	default:
		break;
	}
}

void KeyboardControlComponent::Render() {

}