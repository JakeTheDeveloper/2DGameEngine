#include<iostream>
#include "../extern/glm/glm.hpp"
#include <lua/lua.h>
#include "Game.h"
#include <SDL2/SDL.h>
#include <time.h>

int main() {
	auto* game = new Game();

	game->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
	auto fpsCounter = 0;
	time_t startTime = time(0);
	while(game->isRunning) {
		if (difftime(time(0), startTime) > 1) {
			std::cout << fpsCounter << std::endl;
			fpsCounter = 0;
			startTime = time(0);
		}
		game->ProcessInput();
		game->Update();
		game->Render();
		fpsCounter++;
	}

	game->Destroy();

	return 0;
}