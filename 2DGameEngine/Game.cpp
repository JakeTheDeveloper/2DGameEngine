
#include <iostream>
#include "Game.h"
#include "AssetManager.h"
#include "TransformComponent.h"
#include "InteractionComponent.h"
#include "SpriteComponent.h"
#include "KeyboardControlComponent.h"
#include "../extern/glm/glm.hpp"
#include "ColliderComponent.h"
#include "InputManager.h"
#include "Terrain.h"


EntityManager manager;
bool Game::isRunning = false;
InteractionManager* Game::interactionManager = new InteractionManager();
InputManager* Game::inputManager = new InputManager();
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
Entity& playerEntity = manager.AddEntity("player", PLAYER_LAYER, true);
Entity Game::cursor = manager.AddEntity("cursor", LayerType::UI_LAYER, false);
SDL_Rect Game::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
Terrain* terrain;

Game::Game() {
	this->isRunning = false;
}

Game::~Game() {
	delete inputManager;
	delete assetManager;
}

void Game::Initialize(const int width, const int height) {
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw std::runtime_error("Error initializing SDL...");
		return;
	}

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
    auto& unit = manager.AddEntity("unit", PLAYER_LAYER, true);
    manager.selectedEntities.push_back(&playerEntity);
    manager.selectedEntities.push_back(&unit);

    assetManager->AddTexture("player", std::string("../assets/images/lowdetailman.png").c_str());
    assetManager->AddTexture("mouse_highlight", std::string("../assets/images/selection.png").c_str());
    assetManager->AddTexture("unit", std::string("../assets/images/lowdetailman.png").c_str());
	assetManager->AddTexture("enemy", std::string("../assets/images/Bigbox.png").c_str());
	assetManager->AddTexture("jungle-tiletexture", std::string("../assets/tilemaps/jungle.png").c_str());

    playerEntity.AddComponent<TransformComponent>(glm::vec2(0, 0), glm::vec2(0.f, 0.f), 64, 64, 1);
	playerEntity.AddComponent<KeyboardControlComponent>(interactionManager);
	playerEntity.AddComponent<SpriteComponent>("player", 1, 1, false,  false);
//	playerEntity.AddComponent<ColliderComponent>("player", 1.f, 1.f, 64, 64);
	playerEntity.AddComponent<InteractionComponent>(*interactionManager);
    playerEntity.AddComponent<MouseControlComponent>();

    unit.AddComponent<TransformComponent>(glm::vec2(50, 100), glm::vec2(0.f), 64, 64, 1);
    unit.AddComponent<SpriteComponent>("unit", 1, 1, false, false);
    unit.AddComponent<MouseControlComponent>();

    cursor.AddComponent<TransformComponent>(glm::vec2(0), glm::vec2(0.0f), 32, 32, 1);
    cursor.AddComponent<CursorComponent>();

	terrain = new Terrain("jungle-tiletexture", MAP_SCALE, 32);
	terrain->LoadTerrain("../assets/tilemaps/jungle.map", 25, 20);
}

void Game::ProcessInput() {
    inputManager->GetInputEvents();
    for(auto& event: inputManager->eventQueue){
        if(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP){
            for(auto& se: manager.selectedEntities){
                if(se->HasComponent<KeyboardControlComponent>()){
                    se->GetComponent<KeyboardControlComponent>()->HandleInput(*event);
                }
            }
        } else if(event->type == SDL_MOUSEBUTTONDOWN){
            for(auto& se: manager.selectedEntities) {
                if (se->HasComponent<MouseControlComponent>())
                    se->GetComponent<MouseControlComponent>()->HandleMouseInput(*event);
            }
        }
    }
    inputManager->ClearEventQueue();
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

	std::cout << playerEntity.GetComponent<TransformComponent>()->position.x << std::endl;
	std::cout << playerEntity.GetComponent<TransformComponent>()->position.y << std::endl;

	HandleCameraMovement();
	interactionManager->HandleInteractions();
//	manager.CheckCollisions();
//	manager.HandleCollisions();
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

	auto tileMapWidth = 25 * 32;
	auto tileMapHeight = 30 * 32; // Why is this 30 * 32?

	camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
	camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

	// clamp
	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;
	camera.x = camera.x > tileMapWidth / MAP_SCALE ? tileMapWidth / MAP_SCALE : camera.x;
	camera.y = camera.y > tileMapHeight / MAP_SCALE ? tileMapHeight / MAP_SCALE : camera.y;
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}