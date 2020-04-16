#pragma once
#include "Game.h"
#include "EntityManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

class KeyboardControlComponent: public Component {
private: 
	float _xVel = 0.f;
	float _yVel = 0.f;
public:
	TransformComponent* ownerTransform;
	SpriteComponent* sprite;

	KeyboardControlComponent();
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
};