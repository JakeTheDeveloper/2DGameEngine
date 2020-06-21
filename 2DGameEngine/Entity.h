#pragma once
#include <vector>
#include <string>
#include <map>
#include "./EntityManager.h"
#include "InteractionComponent.h"
#include "./Component.h"
#include <math.h>
#include <typeinfo>
struct EntityManager;
struct Component;
struct InteractionComponent;

struct EntityParams{
    EntityParams(){};
    std::string name;
    LayerType layer;
};

struct Entity {
	std::vector<Component*> components;
	std::map<const std::type_info*, Component*> componentTypeMap;
	EntityManager& manager;
	std::string Name;
	LayerType layer;
	FacingDirection facingDirection;
	bool IsActive;
	Entity(std::string name, LayerType layer);
	void Update(float deltaTime);
	void Render();
	void Destroy();

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args) {
		T* newComponent(new T(std::forward<TArgs>(args)...));

		newComponent->owner = this;
		
		components.emplace_back(newComponent);
		componentTypeMap[&typeid(*newComponent)] = newComponent;

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