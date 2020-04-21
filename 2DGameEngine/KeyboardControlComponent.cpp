#include "KeyboardControlComponent.h"
#include <iostream>

KeyboardControlComponent::KeyboardControlComponent() {
	
}

void KeyboardControlComponent::Initialize() {
	ownerTransform = owner->GetComponent<TransformComponent>();
	sprite = owner->GetComponent<SpriteComponent>();
}

void KeyboardControlComponent::Update(float deltaTime) {
	ownerTransform->position.x += _xVel;
	ownerTransform->position.y += _yVel;
}

void KeyboardControlComponent::HandleInput(SDL_Event& sdlEvent) {
	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		switch (sdlEvent.key.keysym.sym) {
		case SDLK_w:
			_yVel = -6;
			break;
		case SDLK_a:
			_xVel = -6;
			break;
		case SDLK_s:
			_yVel = 6;
			break;
		case SDLK_d:
			_xVel = 6;
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