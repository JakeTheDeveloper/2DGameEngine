#pragma once
#include <string>

const uint32_t WINDOW_WIDTH = 1200;
const uint32_t WINDOW_HEIGHT = 800;

const float FPS = 60;
const float FRAME_TARGET_TIME = 1000 / FPS;

enum CollisionType {
	NO_COLLISION,
	PLAYER_ENEMY_COLLISION,
	PLAYER_VEGETATION_COLLISION,
};

enum LayerType {
	TILEMAP_LAYER = 0,
	VEGETATION_LAYER = 1,
	ENEMY_LAYER = 2,
	PLAYER_LAYER = 3,
	PROJECTILE_LAYER = 4,
	UI_LAYER = 5
};

const uint32_t NUM_LAYERS = 6;

// external vs internal linkage here... Google dat.
const char* const COLLISION_TEXTURE_ID = "collision";