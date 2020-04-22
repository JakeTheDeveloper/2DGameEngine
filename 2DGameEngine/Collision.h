#pragma once
#include <SDL.h>
#include "Constants.h"
class Entity;

class Collision {
public:
	static bool CheckRectangleCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
};

struct CollisionEvent {
	CollisionType collisionType;
	Entity& collidingEntity;
	Entity& colidedEntity;
};