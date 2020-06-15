#include<iostream>
#include "../extern/glm/glm.hpp"
//#include <lua.h>
#include "Game.h"
#include <SDL.h>
#include <time.h>

extern "C" {
#include "../extern/lua/lua.h"
#include "../extern/lua/lauxlib.h"
#include "../extern/lua/lualib.h"
}

#include "LuaBridge.h"

void printMessage(const std::string& s) {
    std::cout << s << std::endl;
}
using namespace luabridge;
int main(int argc, char* argv[]) {
	auto* game = new Game();

    lua_State* L = luaL_newstate();
    luaL_dofile(L, "../assets/scripts/script.lua");
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);

    LuaRef t = getGlobal(L, "window");
    LuaRef title = t["title"];
    auto width = t["width"];
    auto height = t["height"];
    auto titleString = title.cast<std::string>();
    auto widthInt = width.cast<int>();
    auto heightInt = height.cast<int>();
    std::cout << titleString << std::endl;
    std::cout << widthInt << std::endl;

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