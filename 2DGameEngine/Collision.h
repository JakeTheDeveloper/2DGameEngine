#pragma once
#include "../extern/SDL2/include/SDL.h"
#include "Constants.h"
class Entity;

struct Collision {
	static bool CheckRectangleCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
};

struct CollisionEvent {
	Entity& collidingEntity;
	Entity& collidedEntity;
};