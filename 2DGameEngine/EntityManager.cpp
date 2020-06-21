#include "EntityManager.h"
#include "Collision.h"
#include "ColliderComponent.h"
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
	Game::cursor.Render();
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

void EntityManager::CheckCollisions() {
	for (auto& collidingEntity : entities) {
		if (collidingEntity->Name.compare("tile") != 0) {
			if (collidingEntity->HasComponent<TransformComponent>()) {
				for (auto& collidedEntity : entities) {
					if (collidedEntity->Name.compare(collidingEntity->Name) != 0 && collidedEntity->HasComponent<TransformComponent>()) {
						if (Collision::CheckRectangleCollision(collidingEntity->GetComponent<ColliderComponent>()->collider, collidedEntity->GetComponent<ColliderComponent>()->collider)) {
							collisionQueue.emplace_back(new CollisionEvent{ *collidingEntity, *collidedEntity });
						}
					}
				}
			}
		}
	}
}
/*
				 Box Collider Layout

				Top Left   Top Right
				________  _________
				|                 |
	  Left Top	|				  | Right Top
				|				  |
				
				|				  |
	  Left Bot.	|				  | Right Bot.
				|_______  ________|
				Bot. Left  Bot. Right
*/

void EntityManager::HandleCollisions() {
	for (auto& ce : collisionQueue) {
		if (ce->collidingEntity.Name == "player")
		{
			auto collidingComponent = ce->collidingEntity.GetComponent<TransformComponent>();
			auto collidedComponent = ce->collidedEntity.GetComponent<TransformComponent>();

			auto isRight = collidingComponent->position.x > collidedComponent->position.x + (collidedComponent->width / 2);
			auto isUp = collidingComponent->position.y < collidedComponent->position.y + (collidedComponent->height / 2);
			auto isLeft = !isRight;
			auto isDown = !isUp;;
			
			if (isDown && isRight) {
				// Colliding along bottom right half of collider
				if (collidingComponent->position.y > collidedComponent->position.y + collidedComponent->height - 10) {
					collidingComponent->velocity.y = collidingComponent->velocity.y < 0 ? 0 : collidingComponent->velocity.y;
				}
				// Colliding along right bottom half of collider
				if (collidingComponent->position.x > collidedComponent->position.x + collidedComponent->width) {
					collidingComponent->velocity.x = collidingComponent->velocity.x < 0 ? 0 : collidingComponent->velocity.x;
				}
				break;
			}
			
			if (isUp && isRight) {
				// Colliding along Right Top half of collider
				if (collidingComponent->position.x > collidedComponent->position.x + collidedComponent->width) {
					collidingComponent->velocity.x = collidingComponent->velocity.x < 0 ? 0 : collidingComponent->velocity.x;
				}
				// Colliding along Top Right half of collider
				if (collidingComponent->position.y + collidingComponent->height - 5 < collidedComponent->position.y && collidingComponent->position.x < (collidedComponent->position.x + collidedComponent->width * 4)) {
					collidingComponent->velocity.y = collidingComponent->velocity.y > 0 ? 0 : collidingComponent->velocity.y;
				}
				break;
			}

			if (isUp && isLeft) {
				// Colliding along Top Left half of collider
				if (collidingComponent->position.y + collidingComponent->height - 10 < collidedComponent->position.y && collidingComponent->position.x < (collidedComponent->position.x + collidedComponent->width / 2)) {
					collidingComponent->velocity.y = collidingComponent->velocity.y > 0 ? 0 : collidingComponent->velocity.y;
				}

				// Colliding along Left Top half of collider
				if (collidingComponent->position.x + collidingComponent->width < collidedComponent->position.x + 10 && collidingComponent->position.y + collidingComponent->height > collidedComponent->position.y + 5) {
					collidingComponent->velocity.x = collidingComponent->velocity.x > 0 ? 0 : collidingComponent->velocity.x;
				}
				break;
			}

			if (isDown && isLeft) {
				// Colliding along left bottom half of collider
				if (collidingComponent->position.y < collidedComponent->position.y + collidedComponent->height) {
					collidingComponent->velocity.x = collidingComponent->velocity.x > 0 ? 0 : collidingComponent->velocity.x;
				}
				// Colliding along bottom left half of collider
				if (collidingComponent->position.y > collidedComponent->position.y + collidedComponent->height - 10) {
					collidingComponent->velocity.y = collidingComponent->velocity.y < 0 ? 0 : collidingComponent->velocity.y;
				}
				break;
			}
		}
	}
	ClearCollisionQueue();
}

void EntityManager::ClearCollisionQueue() {
	if (collisionQueue.size() > 0) {
		for (auto ce : collisionQueue) {
			delete ce;
		}
		collisionQueue.clear();
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
