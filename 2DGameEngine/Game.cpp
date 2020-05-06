#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "AssetManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "KeyboardControlComponent.h"
#include "glm.hpp"
#include "ColliderComponent.h"
#include "Terrain.h"

extern "C" {
#include "../extern/lua/include/lua.h"
#include "../extern/lua/include/lauxlib.h"
#include "../extern/lua/include/lualib.h"
}

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
Entity& playerEntity = manager.AddEntity("player", PLAYER_LAYER);
SDL_Rect Game::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
Terrain* terrain;

Game::Game() {
	this->isRunning = false;
}

Game::~Game() {
	
}

void Game::Initialize(const int width, const int height) {
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw std::runtime_error("Error initializing SDL...");
		return;
	}

	std::string cmd = "a = 7 + 11";

	lua_State* L = luaL_newstate();

	int r = luaL_dostring(L, cmd.c_str());

	if (r == LUA_OK) {
		lua_getglobal(L, "a");
		if (lua_isnumber(L, -1)) {
			float a_in_cpp = (float)lua_tonumber(L, -1);
			std::cout << a_in_cpp << std::endl;
		}
	}
	else {
		std::string errorMsg = lua_tostring(L, -1);
		std::cout << errorMsg << std::endl;
	}

	lua_close(L);
	
	window = SDL_CreateWindow("2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

	if(!window) {
		throw std::runtime_error("Error creating SDL window");
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(!renderer) {
		throw std::runtime_error("Error creating renderer");
		return;
	}

	LoadLevel(0);

	isRunning = true;
	return;
}


void Game::LoadLevel(uint32_t level) {
	auto& enemy = manager.AddEntity("enemy", PLAYER_LAYER);
	assetManager->AddTexture(COLLISION_TEXTURE_ID, "../assets/images/collisiontexture.png");

	assetManager->AddTexture("player", std::string("../assets/images/AppleMan.png").c_str());
	assetManager->AddTexture("enemy", std::string("../assets/images/Bigbox.png").c_str());
	assetManager->AddTexture("jungle-tiletexture", std::string("../assets/tilemaps/jungle.png").c_str());

	playerEntity.AddComponent<TransformComponent>(glm::vec2(1300.f, 800.f), glm::vec2(0.f, 0.f), 100, 100, 1);
	playerEntity.AddComponent<KeyboardControlComponent>();
	playerEntity.AddComponent<SpriteComponent>("player", 1, 1.f, false,  false);
	playerEntity.AddComponent<ColliderComponent>("player", 1300.f, 800.f, 32, 32);

	enemy.AddComponent<TransformComponent>(glm::vec2(1350.f, 850.f), glm::vec2(0.f, 0.f), 200, 200, 1);
	enemy.AddComponent<SpriteComponent>("enemy", 1, 1.f, false, false);
	enemy.AddComponent<ColliderComponent>("enemy", 1350.f, 850.f, 200, 200);

	terrain = new Terrain("jungle-tiletexture", 4, 32);
	terrain->LoadTerrain("../assets/tilemaps/jungle.map", 25, 20);
}

void Game::ProcessInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			manager.GetEntityByName("player").GetComponent<KeyboardControlComponent>()->HandleInput(event);
			break;
		};
	}
}

void Game::Update() {
	auto delay = (FRAME_TARGET_TIME - (SDL_GetTicks() - _ticksLastFrame));
	
	if(delay > 0 && delay <= FRAME_TARGET_TIME) {
		SDL_Delay(delay);
	}

	deltaTime = (SDL_GetTicks() - _ticksLastFrame) / 1000;
	deltaTime = (deltaTime > 0.05) ? 0.05f : deltaTime;
	_ticksLastFrame = SDL_GetTicks();

	manager.Update(deltaTime);

	HandleCameraMovement();
	manager.CheckCollisions();
	manager.HandleCollisions();
}

void Game::Render() {
	// Set Background color
	SDL_SetRenderDrawColor(renderer, 42, 75, 49, 255);
	// Clear the back buffer
	SDL_RenderClear(renderer);

	if(manager.HasNoEntities()) {
		return;
	}

	manager.Render();

	// swap front and back buffers
	SDL_RenderPresent(renderer);
}

void Game::HandleCameraMovement() {
	auto* mainPlayerTransform = playerEntity.GetComponent<TransformComponent>();

	camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
	camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

	// clamp
	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;
	camera.x = camera.x > WINDOW_WIDTH ? WINDOW_WIDTH : camera.x;
	camera.y = camera.y > WINDOW_HEIGHT ? WINDOW_HEIGHT : camera.y;
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}