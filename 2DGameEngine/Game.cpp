#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "AssetManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "KeyboardControlComponent.h"
#include "glm.hpp"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;

Game::Game() {
	this->isRunning = false;
}

Game::~Game() {
	
}

void Game::Initialize(const int width, const int height) {
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
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
	assetManager->AddTexture("appleguy", std::string("../assets/images/AppleMan.png").c_str());

	auto& chopperEntity(manager.AddEntity("appleguy"));
	chopperEntity.AddComponent<TransformComponent>(glm::vec2(400.f, 300.f), glm::vec2(0.f, 0.f), 32, 32, 1);
	chopperEntity.AddComponent<SpriteComponent>("appleguy", 2, 1.f, false,  false);
	chopperEntity.AddComponent<KeyboardControlComponent>();
}

void Game::ProcessInput() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type) {
		case SDL_QUIT:
			isRunning = false; 
			break;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE) 
				isRunning = false;
		default:
			break;
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

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}