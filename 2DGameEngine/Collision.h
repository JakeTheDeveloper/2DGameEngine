#pragma once
#include <SDL2/SDL.h>
#include "Constants.h"
struct Entity;

struct Collision {
	static bool CheckRectangleCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
};

struct CollisionEvent {
	Entity& collidingEntity;
	Entity& collidedEntity;
};