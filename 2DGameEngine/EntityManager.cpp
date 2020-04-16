#include "EntityManager.h"

void EntityManager::ClearData() {
	for(auto& entity : _entities) {
		entity->Destroy();
	}
}

void EntityManager::Update(float deltaTime) {
	for(auto &entity : _entities) {
		entity->Update(deltaTime);
	}
}

void EntityManager::Render() {
	for(auto &entity : _entities) {
		entity->Render();
	}
}

Entity& EntityManager::AddEntity(std::string entityName) {
	auto* entity = new Entity(*this, entityName);
	_entities.emplace_back(entity);
	return *entity;
}

bool EntityManager::HasNoEntities() {
	return (_entities.size() == 0);
}

std::vector<Entity*> EntityManager::GetEntities() const {
	return _entities;
}

uint32_t EntityManager::GetEntityCount() {
	return _entities.size();
}