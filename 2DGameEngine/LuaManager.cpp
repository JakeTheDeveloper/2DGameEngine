#include "LuaManager.h"
#include "Game.h"
#include "KeyboardControlComponent.h"
#include "Vector.h"

LuaManager::LuaManager() {
    L = luaL_newstate();
    luaL_openlibs(L);
}

LuaManager::~LuaManager() {
    lua_close(L);
}

void LuaManager::CreateEntityFromScript(std::string scriptName) {
    luaL_dofile(L, scriptName.c_str());
    auto table_ref = luabridge::getGlobal(L, "Entity");
    if(table_ref.isTable()) {
        auto name = table_ref["name"].isString() ? table_ref["name"].tostring() : "NULL";
        auto layerStr = table_ref["layer"].isString() ? table_ref["layer"].tostring() : "NULL";
        auto layerEnum = LayerTypeEnumTable.find(layerStr);

        if(layerEnum != LayerTypeEnumTable.end()){
            Game::manager.AddEntity(name, layerEnum->second);
            auto components = table_ref["components"];
            AddComponentsToEntity(Game::manager.GetEntityByName(name), components);
        } else {
            throw std::runtime_error("[LuaManager.cpp] Unable to find layer type");
        }

    } else {
        throw std::runtime_error("Entity is not a table!");
    }
}

void LuaManager::AddComponentsToEntity(Entity& e, luabridge::LuaRef componentTable){
        if(componentTable.isTable()){
            try{
                for (auto& pair : getKeyValueMap(componentTable)) {
                    auto& key = pair.first;
                    auto& value = pair.second;
                    if(key.compare("TransformComponent") == 0){
                        auto position = glm::vec2(value["x"].cast<int>(), value["y"].cast<int>());
                        e.AddComponent<TransformComponent>(position, glm::vec2(0.f), value["width"].cast<int>(), value["height"].cast<int>(), 1);
                    } else if(key.compare("KeyboardControlComponent") == 0) {
                        auto movementSpeed = value["movementSpeed"].cast<int>();
                        e.AddComponent<KeyboardControlComponent>(movementSpeed);
                    } else if(key.compare("MouseControlComponent") == 0){
                        e.AddComponent<MouseControlComponent>();
                    } else if(key.compare("SpriteComponent") == 0){
                        // TODO: break this into it's own method and add error handling for each component
                        auto textureId = value["textureId"].tostring();
                        auto numFrames = value["numFrames"].cast<int>();
                        auto animationSpeed = value["animationSpeed"].cast<int>();
                        auto hasDirection = value["hasDirection"].cast<bool>();
                        auto isFixed = value["isFixed"].cast<bool>();
                        e.AddComponent<SpriteComponent>(textureId, numFrames, animationSpeed, hasDirection, isFixed);
                    } else if(key.compare("CursorComponent") == 0) {
                        e.AddComponent<CursorComponent>();
                    }else{
                            throw std::runtime_error("[LuaManager.cpp] Unable to find component: " + key);
                    }
                }
            } catch (luabridge::LuaException ex){
                std::cout << ex.what() << std::endl;
            }
        }
}

std::unordered_map<std::string, luabridge::LuaRef> LuaManager::getKeyValueMap(const luabridge::LuaRef& table) {
    using namespace luabridge;
    std::unordered_map<std::string, LuaRef> result;
    if (table.isNil()) { return result; }

    auto state = table.state();
    push(state, table); // push table

    lua_pushnil(state);  // push nil, so lua_next removes it from stack and puts (k, v) on stack
    while (lua_next(state, -2) != 0) { // -2, because we have table at -1
        if (lua_isstring(state, -2)) { // only store stuff with string keys
            result.emplace(lua_tostring(L, -2), LuaRef::fromStack(L, -1));
        }
        lua_pop(state, 1); // remove value, keep key for lua_next
    }

    lua_pop(state, 1); // pop table
    return result;
}

void LuaManager::LoadEntitesFromScript(std::string entitiesScript) {
    luaL_dofile(L, entitiesScript.c_str());
    auto entitie_tableRef = luabridge::getGlobal(L, "Entities");
    if(entitie_tableRef.isTable()){
        auto entities  = entitie_tableRef.cast<std::vector<std::string>>();
        for(auto entitiyScript: entities){
            CreateEntityFromScript(entitiyScript);
        }
    }else{
        throw std::runtime_error("Could not loading entities from script");
    }
}
