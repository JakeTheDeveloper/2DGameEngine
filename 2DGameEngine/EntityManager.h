#pragma once

#include "./Entity.h"
#include "./Component.h"
#include "Collision.h"
#include <vector>
#include "glm.hpp"
class EntityManager {
private:
public:
	std::vector<CollisionEvent*> collisionQueue;
	std::vector<Entity*> entities;
	void ClearData();
	void Update(float deltaTime);
	void Render();
	bool HasNoEntities();
	Entity& AddEntity(std::string entityName, LayerType layerType);
	std::vector<Entity*> GetEntitiesByLayer(LayerType layerType) const;
	std::vector<Entity*> GetEntities() const;
	uint32_t GetEntityCount() const;
	Entity& GetEntityByName(std::string name) const;
	void HandleCollisions();
	void CheckCollisions();
	void ClearCollisionQueue();
};