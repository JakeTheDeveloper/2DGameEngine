#pragma once

#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_ttf.h>
#include "Entity.h"
#include "MouseControlComponent.h"
#include "Component.h"
#include "EntityManager.h"
#include "AssetManager.h"

// vvv Don't remove this otherwise SDL dies.
#undef main

struct AssetManager;
struct InputManager;

struct Game {
private:
	SDL_Window* window;
	float _ticksLastFrame = 0.0f;
	
public:
	Game();
	~Game();
	
	static SDL_Renderer* renderer;
	static InteractionManager* interactionManager;
	static InputManager* inputManager;
	static AssetManager* assetManager;
	static SDL_Rect camera;
    static glm::vec2 mousePos;
    static bool isRunning;
    float deltaTime = 0.0f;
	void LoadLevel(uint32_t levelNumber);
	void Initialize(const int width, const int height);
    void ProcessInput();
	void Update();
	void Render();
	void HandleCameraMovement();
	void Destroy();
};