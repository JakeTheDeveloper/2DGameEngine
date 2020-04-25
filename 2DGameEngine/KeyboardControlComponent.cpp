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

	if (_xVel > 50) {
		_xVel = 50;
	}
	
	if (_xVel < -50) {
		_xVel = -50;
	}

	if (_yVel > 50) {
		_yVel = 50;
	}

	if (_yVel < -50) {
		_yVel = -50;
	}

	ownerTransform->velocity.x += _xVel;
	ownerTransform->velocity.y += _yVel;

}

void KeyboardControlComponent::HandleInput(SDL_Event& sdlEvent) {
	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		switch (sdlEvent.key.keysym.sym) {
		case SDLK_w:
			_yVel = -6.f;
			break;
		case SDLK_a:
			_xVel = -6.f;
			break;
		case SDLK_s:
			_yVel = 6.f;
			break;
		case SDLK_d:
			_xVel = 6.f;
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