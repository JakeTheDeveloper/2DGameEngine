#include "EntityManager.h"
#include "Collision.h"
#include <iostream>
void EntityManager::ClearData() {
	for(auto& entity : entities) {
		entity->Destroy();
	}
}

void EntityManager::Update(float deltaTime) {
	for(auto &entity : entities) {
		entity->Update(deltaTime);
	}
}

void EntityManager::Render() {
	for (auto layerNum = 0; layerNum < NUM_LAYERS; layerNum++) {
		for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNum))) {
			entity->Render();
		}
	}
}

Entity &EntityManager::AddEntity(std::string entityName, LayerType layerType) {
	auto* entity = new Entity(entityName, layerType);
	entities.emplace_back(entity);
	return *entity;
}

bool EntityManager::HasNoEntities() {
	return (entities.size() == 0);
}

std::vector<Entity*> EntityManager::GetEntities() const {
	return entities;
}

uint32_t EntityManager::GetEntityCount() const {
	return entities.size();
}

Entity& EntityManager::GetEntityByName(std::string name) const {
	for (auto& entity : entities) {
		if (entity->Name.compare(name) == 0)
			return *entity;
	}
}

// TODO: Fix this 
std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const {
	std::vector<Entity*> selectedEntities;
	for(auto& entity: entities)	{
		if (entity->layer == layer) {
			selectedEntities.emplace_back(entity);
		}
	}
	return selectedEntities;
}

EntityManager::~EntityManager() {
    if(entities.size() > 0) {
        for(auto e: entities)
            delete e;
    }
    selectedEntities.clear();
    interactableEntities.clear();
}
