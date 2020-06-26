
#include <iostream>
#include "Game.h"
#include "AssetManager.h"
#include "TransformComponent.h"
#include "InteractionComponent.h"
#include "SpriteComponent.h"
#include "KeyboardControlComponent.h"
#include "../extern/glm/glm.hpp"
#include "InputManager.h"
#include "Terrain.h"
#include "LuaBridge/Vector.h"
#include <unordered_map>


bool Game::isRunning = false;

EntityManager Game::manager;
LuaManager* Game::luaManager = new LuaManager();
WorldManager* Game::worldManager = new WorldManager();
InteractionManager* Game::interactionManager = new InteractionManager();
InputManager* Game::inputManager = new InputManager();
AssetManager* Game::assetManager = new AssetManager(&manager);


SDL_Renderer* Game::renderer;

//SDL_Rect Game::Camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
Terrain* terrain;

Game::Game() {
	this->isRunning = false;
}


Game::~Game() {
    if(inputManager != nullptr)
	    delete inputManager;
    if(assetManager != nullptr)
	    delete assetManager;
    if(luaManager != nullptr){
        delete luaManager;
    }
}

void Game::Initialize(const int width, const int height) {
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw std::runtime_error("Error initializing SDL...");
	}

	window = SDL_CreateWindow("2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

	if(!window) {
		throw std::runtime_error("Error creating SDL window");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(!renderer) {
		throw std::runtime_error("Error creating renderer");
	}

	LoadLevel(0);

	isRunning = true;
}

void Game::LoadLevel(uint32_t level) {
    assetManager->AddTexture("player", std::string("../assets/images/lowdetailman.png").c_str());
    assetManager->AddTexture("mouse_highlight", std::string("../assets/images/selection.png").c_str());
	assetManager->AddTexture("enemy", std::string("../assets/images/Bigbox.png").c_str());
	assetManager->AddTexture("jungle-tiletexture", std::string("../assets/tilemaps/jungle.png").c_str());

	luaManager->CreateEntityFromScript("../assets/scripts/player.lua");
    luaManager->CreateEntityFromScript("../assets/scripts/camera.lua");
    luaManager->CreateEntityFromScript("../assets/scripts/cursor.lua");

    manager.selectedEntities.push_back(&manager.GetEntityByName("player"));

	terrain = new Terrain("jungle-tiletexture", MAP_SCALE, TILE_SIZE);
	terrain->LoadTerrain("../assets/tilemaps/jungle.map", MAP_SIZE_X, MAP_SIZE_Y);
}

void Game::ProcessInput() {
    inputManager->GetInputEvents();
    for(auto& event: inputManager->eventQueue){
        if(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP){
            for(auto& e: manager.entities){
                if(e->HasComponent<KeyboardControlComponent>()){
                    e->GetComponent<KeyboardControlComponent>()->HandleInput(*event);
                }
            }
        } else if(event->type == SDL_MOUSEBUTTONDOWN){
            for(auto& e: manager.entities) {
                if (e->HasComponent<MouseControlComponent>())
                    e->GetComponent<MouseControlComponent>()->HandleMouseInput(*event);
            }
        }
    }
    inputManager->ClearEventQueue();
}

void Game::Update() {
	auto delay = (FRAME_TARGET_TIME - (SDL_GetTicks() - _ticksLastFrame));

//	if(delay > 0 && delay <= FRAME_TARGET_TIME) {
//		SDL_Delay(delay);
//	}

	deltaTime = ((SDL_GetTicks() - _ticksLastFrame) / 1000) > 0.05 ? 0.05 : ((SDL_GetTicks() - _ticksLastFrame) / 1000);
	_ticksLastFrame = SDL_GetTicks();

	manager.Update(deltaTime);
	std::cout << manager.GetEntityByName("camera").GetComponent<TransformComponent>()->position.x << std::endl;

	HandleCameraMovement();
	interactionManager->HandleInteractions();
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

// TODO CameraComponent
void Game::HandleCameraMovement() {
//	auto* mainPlayerTransform = manager.GetEntityByName("player").GetComponent<TransformComponent>();
//    auto camera = manager.GetEntityByName("camera").GetComponent<TransformComponent>()->position;
//
//    auto tileMapWidth = 25 * 32;
//    auto tileMapHeight = 30 * 32; // Why is this 30 * 32?
//
//    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
//    camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);
//
//    // clamp
//	camera.x = camera.x < 0 ? 0 : camera.x;
//    camera.y = camera.y < 0 ? 0 : camera.y;
//    camera.x = camera.x > tileMapWidth / MAP_SCALE ? tileMapWidth / MAP_SCALE : camera.x;
//    camera.y = camera.y > tileMapHeight / MAP_SCALE ? tileMapHeight / MAP_SCALE : camera.y;
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}