#include "EntityManager.h"
#include "Collision.h"
#include "ColliderComponent.h"

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

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer) {
	auto* entity = new Entity(*this, entityName, layer);
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

std::string EntityManager::CheckEntityCollisions(Entity& srcEntity) const {
	auto* myCollider = srcEntity.GetComponent<ColliderComponent>();
	for (auto& entity : entities) {
		if (entity->Name.compare(srcEntity.Name) != 0 && entity->Name.compare("Tile") != 0) {
			if (entity->HasComponent<ColliderComponent>()) {
				auto* entityCollider = entity->GetComponent<ColliderComponent>();
				if (Collision::CheckRectangleCollision(myCollider->collider, entityCollider->collider)) {
					return entityCollider->colliderTag;
				}
			}
		}
	}
	return std::string();
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