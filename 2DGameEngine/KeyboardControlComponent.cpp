#include "KeyboardControlComponent.h"

KeyboardControlComponent::KeyboardControlComponent() {
	
}

void KeyboardControlComponent::Initialize() {
	ownerTransform = owner->GetComponent<TransformComponent>();
	sprite = owner->GetComponent<SpriteComponent>();
}

void KeyboardControlComponent::Update(float deltaTime) {
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_w:
						_yVel = -1;
						break;
					case SDLK_a:
						_xVel = -1;
						break;
					case SDLK_s:
						_yVel = 1;
						break;
					case SDLK_d:
						_xVel = 1;
						break;
					default:
						break;
				}
				break;

			case SDL_KEYUP:
				switch(event.key.keysym.sym) {
					case SDLK_w:
						if(_yVel < 0)
							_yVel = 0;
						break;
					case SDLK_a:
						if(_xVel < 0)
							_xVel = 0;
						break;
					case SDLK_s:
						if(_yVel > 0)
							_yVel = 0;
						break;
					case SDLK_d:
						if(_xVel > 0)
							_xVel = 0;
						break;
				}
				break;

			default:
				break;
		};
	}
	ownerTransform->position.x += _xVel;
	ownerTransform->position.y += _yVel;
}

void KeyboardControlComponent::Render() {

}