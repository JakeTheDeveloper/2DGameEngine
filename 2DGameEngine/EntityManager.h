#pragma once

#include "./Entity.h"
#include "./Component.h"
#include <vector>
class EntityManager {
private:
	std::vector<Entity*> _entities;
public:
	void ClearData();
	void Update(float deltaTime);
	void Render();
	bool HasNoEntities();
	Entity& AddEntity(std::string entityName);
	std::vector<Entity*> GetEntities() const;
	uint32_t GetEntityCount();
};