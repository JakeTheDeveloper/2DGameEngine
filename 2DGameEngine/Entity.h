#pragma once
#include <vector>
#include <string>
#include <map>
#include "Constants.h"
#include "./EntityManager.h"
#include "InteractionComponent.h"
#include "./Component.h"
#include <math.h>
#include <typeinfo>
struct EntityManager;
struct Component;
struct InteractionComponent;

struct Entity {
private:
	std::vector<Component*> _components;
	std::map<const std::type_info*, Component*> componentTypeMap;
public:
	EntityManager& manager;
	std::string Name;
	LayerType layer;
	bool IsActive;
	Entity(EntityManager& manager);
	Entity(EntityManager& manager, std::string name, LayerType layerType);
	void Update(float deltaTime);
	void Render();
	void Destroy();

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args) {
		T* newComponent(new T(std::forward<TArgs>(args)...));

		newComponent->owner = this;
		
		_components.emplace_back(newComponent);
		componentTypeMap[&typeid(*newComponent)] = newComponent;

		 if (typeid(T).name() == typeid(InteractionComponent).name()) {
		 	this->manager.interactableEntities.push_back(this);
		 }

		newComponent->Initialize();
		
		return *newComponent;
	}

	template <typename T>
	bool HasComponent() const {
		return componentTypeMap.count(&typeid(T));
	}

	template <typename T>
	T* GetComponent() {
		return static_cast<T*>(componentTypeMap[&typeid(T)]);
	}
};