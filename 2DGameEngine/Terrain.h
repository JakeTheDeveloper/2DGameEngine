#pragma once
#include "Game.h"
#include "EntityManager.h"
#include "TileComponent.h"
#include <fstream>
class Terrain {
private:
	std::string _textureId;
	uint16_t _scale;
	uint16_t _tileSize;

public:
	Terrain(std::string textureId, uint16_t scale, uint16_t tileSize);
	~Terrain();
	void LoadTerrain(std::string filePath, uint32_t mapSizeX, uint32_t mapSizeY);
	void AddTile(uint32_t sourceX, uint32_t sourceY, uint32_t x, uint32_t y);
};