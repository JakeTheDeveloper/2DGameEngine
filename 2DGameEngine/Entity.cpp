#include "Entity.h"
#include "Game.h"

Entity::Entity(std::string name, LayerType layer) : manager(Game::manager), Name(name), layer(layer) {
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