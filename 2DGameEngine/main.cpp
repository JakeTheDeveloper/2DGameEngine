#include<iostream>
#include <glm.hpp>
#include <lua.h>
#include "Game.h"
#include "Constants.h"

int main() {
	auto* game = new Game();

	game->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

	while(game->isRunning) {
		game->ProcessInput();
		game->Update();
		game->Render();
	}

	game->Destroy();

	return 0;
}