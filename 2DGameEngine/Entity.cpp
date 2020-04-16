#include "Entity.h"

Entity::Entity(EntityManager& manager): _manager(manager) {
	this->IsActive = true;
}

Entity::Entity(EntityManager& manager, std::string name) : _manager(manager), Name(name) {
	this->IsActive = true;
}

void Entity::Update(float deltaTime) {
	for(auto& component : _components) {
		component->Update(deltaTime);
	}
}

void Entity::Render() {
	for(auto& component : _components) {
		component->Render();
	}
}

void Entity::Destroy() {
	this->IsActive = false;
}