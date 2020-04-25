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

void EntityManager::HandleCollisions() {
	for (auto& ce : collisionQueue) {
		if (ce->collidingEntity.Name == "player")
		{
			auto collidingComponent = ce->collidingEntity.GetComponent<TransformComponent>();
			auto collidedComponent = ce->collidedEntity.GetComponent<TransformComponent>();

			auto xDiff = collidingComponent->position.x - collidedComponent->position.x;
			auto yDiff = collidingComponent->position.y - collidedComponent->position.y;

			auto isRight = collidingComponent->position.x > collidedComponent->position.x + (collidedComponent->width / 2);
			auto isLeft = collidingComponent->position.x < collidedComponent->position.x  + (collidedComponent->width / 2);
			auto isUp = collidingComponent->position.y < collidedComponent->position.y + (collidedComponent->height / 2);
			auto isDown = collidingComponent->position.y > collidedComponent->position.y + (collidedComponent->height / 2);

			std::cout << "Is Right: " << isRight << std::endl;
			std::cout << "Is Left: " << isLeft << std::endl;
			std::cout << "Is Up: " << isUp << std::endl;
			std::cout << "Is Down: " << isDown << std::endl << std::endl;

			std::cout << "yDiff: " << yDiff << std::endl;
			std::cout << "xDiff: " << xDiff << std::endl << std::endl;

			
			if (isDown && isRight) {
				// Colliding along bottom right half of collider
				if (yDiff > xDiff) {
					collidingComponent->velocity.y = collidingComponent->velocity.y < 0 ? 0 : collidingComponent->velocity.y;
				}
				// Colliding along right bottom half of collider
				if (xDiff > yDiff) {
					collidingComponent->velocity.x = collidingComponent->velocity.x < 0 ? 0 : collidingComponent->velocity.x;
				}
			}
			
			if (isUp && isRight) {
				if (xDiff > yDiff) {
					//// Colliding along Right Top half of collider
					if (collidingComponent->position.x > collidedComponent->position.x + collidedComponent->width) {
						collidingComponent->velocity.x = collidingComponent->velocity.x < 0 ? 0 : collidingComponent->velocity.x;
					}
					// Colliding along Top Right half of collider
					if (collidingComponent->position.y + collidingComponent->height - 5 < collidedComponent->position.y && collidingComponent->position.x < (collidedComponent->position.x + collidedComponent->width * 4)) {
						collidingComponent->velocity.y = collidingComponent->velocity.y > 0 ? 0 : collidingComponent->velocity.y;
					}
				}

				if (xDiff < yDiff) {
					collidingComponent->velocity.x = collidingComponent->velocity.x < 0 ? 0 : collidingComponent->velocity.x;
				}
			}

			if (isUp && isLeft) {
				if (xDiff > yDiff) {
					collidingComponent->velocity.y = collidingComponent->velocity.y > 0 ? 0 : collidingComponent->velocity.y;
				}

				if (xDiff < yDiff) {
					collidingComponent->velocity.x = collidingComponent->velocity.x > 0 ? 0 : collidingComponent->velocity.x;
				}
			}

			if (isDown && isLeft) {
				// Colliding along left bottom half of collider
				if (collidingComponent->position.y < collidedComponent->position.y + collidedComponent->width) {
					collidingComponent->velocity.x = collidingComponent->velocity.x > 0 ? 0 : collidingComponent->velocity.x;
				}
				// Colliding along bottom left half of collider
				if (collidingComponent->position.y > collidedComponent->position.y + collidedComponent->height) {
					collidingComponent->velocity.y = collidingComponent->velocity.y < 0 ? 0 : collidingComponent->velocity.y;
				}
			}
			
			std::cout << "YDIFF:" << yDiff << std::endl;
			std::cout << "XDIFF:" << xDiff << std::endl << std::endl;
		}
	}
	ClearCollisionQueue();
}

void EntityManager::ClearCollisionQueue() {
	if (collisionQueue.size() > 0)
	{
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