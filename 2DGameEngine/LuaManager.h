#pragma once
extern "C" {
#include "../extern/lua/lua.h"
#include "../extern/lua/lauxlib.h"
#include "../extern/lua/lualib.h"
}
#include "LuaBridge.h"
#include "Entity.h"
#include <unordered_map>

struct LuaManager {
    lua_State* L;

    LuaManager();
    ~LuaManager();
    void CreateEntityFromScript(std::string scriptName);
    void LoadEntitesFromScript(std::string entitiesScript);
    std::unordered_map<std::string, luabridge::LuaRef> getKeyValueMap(const luabridge::LuaRef& table);

private:
    void AddComponentsToEntity(Entity& e, luabridge::LuaRef componentTable);
};