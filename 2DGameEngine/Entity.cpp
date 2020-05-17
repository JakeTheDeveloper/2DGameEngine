#include "Entity.h"

Entity::Entity(EntityManager& manager): manager(manager) {
	this->IsActive = true;
}

Entity::Entity(EntityManager& manager, std::string name, LayerType layerType) : manager(manager), Name(name), layer(layerType) {
	this->IsActive = true;
}

void Entity::Update(float deltaTime) {
	for(auto& component : components) {
		component->Update(deltaTime);
	}
}

void Entity::Render() {
	for(auto& component : components) {
		component->Render();
	}
}

void Entity::Destroy() {
	this->IsActive = false;
}