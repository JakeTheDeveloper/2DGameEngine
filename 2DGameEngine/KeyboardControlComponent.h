#pragma once
#include "Game.h"
#include "EntityManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "InteractionManager.h"

struct KeyboardControlComponent: public Component {
private: 
	float _xVel = 0.f;
	float _yVel = 0.f;
public:
	int movementSpeed;
	KeyboardControlComponent(int movementSpeed);
	void HandleInput(SDL_Event event);
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
};