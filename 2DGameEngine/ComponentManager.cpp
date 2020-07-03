#include "ComponentManager.h"

template<typename ComponentType>
ComponentInstance ComponentManager<ComponentType>::add(Entity e, ComponentType &c) {
    // newInstance is the uint index for the array
    ComponentInstance newInstance = { componentData.size() };
    // since we're made a std::array[1024] we set the newInstance index equal to the component
    componentData.data[newInstance.index] = c;
    // entityMap keeps track of all the entities linked with this component
    entityMap[e] = newInstance;
    componentData.size++;
    return newInstance;
}

template<typename ComponentType>
ComponentType *ComponentManager<ComponentType>::get(Entity e) {
    ComponentInstance instance = entityMap[e];
    return &componentData.data[instance.index];
}

template<typename ComponentType>
void ComponentManager<ComponentType>::destroy(Entity e) {

}