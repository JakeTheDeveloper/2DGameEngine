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
    luaL_openlibs(L);
    // Register functions before loading the script file
    getGlobalNamespace(L).
        beginNamespace("game").
            addFunction("printMessage", printMessage)
        .endNamespace();
    luaL_dofile(L, "../assets/scripts/script.lua");
    lua_pcall(L, 0, 0, 0);
    LuaRef sumNumbers = getGlobal(L, "sumNumbers");
    int result = sumNumbers(5, 4);
    std::cout << "Result: " << result << std::endl;

//    LuaRef t = getGlobal(L, "window");
//    LuaRef title = t["title"];
//    auto size = t["size"];
//    auto width = size["width"];
//    auto height = size["height"];
//    auto titleString = title.cast<std::string>();
//    auto widthInt = width.cast<int>();
//    auto heightInt = height.cast<int>();
//    std::cout << titleString << std::endl;
//    std::cout << widthInt << std::endl;



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