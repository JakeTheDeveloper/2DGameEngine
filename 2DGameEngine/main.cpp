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

void printMessage(const std::string& s) {
    std::cout << s << std::endl;
}

int lua_HostFunction(lua_State *L){
    std::cout << lua_gettop(L) << std::endl;
    float a = (float)lua_tonumber(L, 1);
    float b = (float)lua_tonumber(L, 2);
    std::cout << "Host function Called" << std::endl;
    float c = a * b;
    lua_pushnumber(L, c);
    // returns number of return vals
    return 1;
}

int main(int argc, char* argv[]) {
	auto* game = new Game();

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    int r = luaL_dofile(L, "../assets/scripts/script.lua");

    lua_register(L, "HostFunction", lua_HostFunction);

    auto width = 0;
    auto height = 0;

    if(r == LUA_OK){
        lua_getglobal(L, "window");
        if(lua_istable(L, -1)){
            lua_pushstring(L, "Width");
            lua_gettable(L, -2);
            width = lua_tonumber(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "Height");
            lua_gettable(L, -2);
            height = lua_tonumber(L, -1);
            lua_pop(L, -1);
        }

        lua_getglobal(L, "AddStuff");
        if(lua_isfunction(L, -1)){
            lua_pushnumber(L, 3.5f);
            lua_pushnumber(L, 7.1f);

            // n = num of params
            // r = num of return vals
            // f = error handling
            lua_pcall(L, 2, 1, 0);

            std::cout << (float)lua_tonumber(L, -1) << std::endl;
        }

        lua_getglobal(L, "DoThing");
        lua_pushnumber(L, 4.0f);
        lua_pushnumber(L, 5.0f);
        lua_pcall(L, 2, 1, 0);
        std::cout << (float)lua_tonumber(L, -1) << std::endl;
    }
    else{
        std::string errormsg = lua_tostring(L, -1);
        std::cout << errormsg << std::endl;
    }

    lua_close(L);

	game->Initialize(width, height);
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