#pragma once
#include <SDL.h>
#include "../extern/glm/glm.hpp"
#include "Component.h"

struct TransformComponent: public Component {
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 direction;
	uint32_t width;
	uint32_t height;
	float topLeft;
	float botLeft;
	float topRight;
	float botRight;
	int scale;
    TransformComponent();
	TransformComponent(glm::vec2 position, glm::vec2 velocity, uint32_t w, uint32_t h, int scale);
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
};
