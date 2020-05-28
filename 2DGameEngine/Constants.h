#pragma once
#include <string>

const uint32_t WINDOW_WIDTH = 1200;
const uint32_t WINDOW_HEIGHT = 800;
const uint32_t MAP_SCALE = 2;


const float FPS = 60;
const float FRAME_TARGET_TIME = 1000 / FPS;

enum class FacingDirection {
	FACING_NONE = 0,
	FACING_LEFT = 1,
	FACING_UP = 2,
	FACING_RIGHT = 4,
	FACING_DOWN = 8
};

static const FacingDirection& operator|=(FacingDirection& a, FacingDirection b) {
	return (FacingDirection&)((int&)a |= (int)b);
};

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

enum InteractionTag {
	PLAYER_TO_OBJECT = 0,
	PLAYER_TO_NPC = 1
};

const uint32_t NUM_LAYERS = 6;

// external vs internal linkage here... Google dat.
const char* const COLLISION_TEXTURE_ID = "collision";