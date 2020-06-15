#pragma once
#include "Constants.h"
#include "Entity.h"

struct WorldManager {
    Entity* tiles[MAP_SIZE_X][MAP_SIZE_Y];
    WorldManager();
    ~WorldManager();
};
