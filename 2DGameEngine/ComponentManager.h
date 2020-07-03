#pragma once
#include "Entity.h"

struct ComponentInstance{
    unsigned int index;
};

template<typename ComponentType>
class ComponentManager {
public:
    ComponentInstance add(Entity e, ComponentType& c);
    ComponentType* get(Entity e);
    void destroy(Entity e);

    struct ComponentData{
        unsigned int size = 1;
        std::array<ComponentType, 1024> data;
    };
private:
    ComponentData componentData;
    std::map<Entity, ComponentInstance> entityMap;
};
