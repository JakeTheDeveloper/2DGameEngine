#include "Terrain.h"

extern EntityManager manager;

Terrain::Terrain(std::string textureId, uint16_t scale, uint16_t tileSize)
	: _textureId(textureId), _scale(scale), _tileSize(tileSize) {

}

Terrain::~Terrain() {

}

void Terrain::LoadTerrain(std::string filePath, uint32_t mapSizeX, uint32_t mapSizeY) {
	std::fstream terrainFile;
	terrainFile.open(filePath);

	SDL_Rect srcRect;
	auto scale = (_scale * _tileSize);

	// y is rows
	// x is column
	for (auto y = 0; y < mapSizeY; y++) {
		for (auto x = 0; x < mapSizeX; x++) {
			char ch;
			terrainFile.get(ch);
			srcRect.y = atoi(&ch) * 32;

			terrainFile.get(ch);
			srcRect.x = atoi(&ch) * 32;

			AddTile(srcRect.x, srcRect.y, x * scale, y * scale);
			terrainFile.ignore();
		}
	}

	terrainFile.close();
}

void Terrain::AddTile(uint32_t sourceX, uint32_t sourceY, uint32_t x, uint32_t y) {
	Entity& newTile(manager.AddEntity("Tile", TILEMAP_LAYER, false));
	newTile.AddComponent<TileComponent>(sourceX, sourceY, x, y, _tileSize, _scale, _textureId);
}