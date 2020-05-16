#pragma once
#include <SDL2/SDL.h>
#include "../extern/glm/glm.hpp"
#include "Game.h"

struct TransformComponent: public Component {
public:
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 direction;
	uint32_t width;
	uint32_t height;
	int scale;

	TransformComponent(glm::vec2 position, glm::vec2 velocity, uint32_t w, uint32_t h, int scale);
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
};