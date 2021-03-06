#include<iostream>
#include "../extern/glm/glm.hpp"
#include "Game.h"
#include <SDL.h>
#include <time.h>
#include "LuaManager.h"

void printMessage(const std::string& s) {
    std::cout << s << std::endl;
}
using namespace luabridge;
int main(int argc, char* argv[]) {
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