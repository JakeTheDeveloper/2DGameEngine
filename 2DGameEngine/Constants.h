#pragma once

const uint32_t WINDOW_WIDTH = 800;
const uint32_t WINDOW_HEIGHT = 600;

const uint32_t FPS = 60;
const uint32_t FRAME_TARGET_TIME = 1000 / FPS;

enum LayerType {
	TILEMAP_LAYER = 0,
	VEGETATION_LAYER = 1,
	ENEMY_LAYER = 2,
	PLAYER_LAYER = 3,
	PROJECTILE_LAYER = 4,
	UI_LAYER = 5
};

const uint32_t NUM_LAYERS = 6;