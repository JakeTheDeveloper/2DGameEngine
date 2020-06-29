#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "EntityManager.h"
#include "Game.h"

struct AssetManager {
private:
	std::map<std::string, SDL_Texture*> textures;
public:
	EntityManager* manager;
	AssetManager(EntityManager* manager);
	~AssetManager();
	void ClearData();
	void AddTexture(std::string textureId, const char* filePath);
	SDL_Texture* GetTexture(std::string textureId);
};