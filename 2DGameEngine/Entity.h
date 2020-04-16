#pragma once
#include <vector>
#include <string>
#include <map>
#include "./EntityManager.h"
#include "./Component.h"

class EntityManager;
class Component;

class Entity {
private:
	EntityManager& _manager;
	std::vector<Component*> _components;
	std::map<const type_info*, Component*> componentTypeMap;
public:
	std::string Name;
	bool IsActive;
	Entity(EntityManager& manager);
	Entity(EntityManager& manager, std::string name);
	void Update(float deltaTime);
	void Render();
	void Destroy();

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args) {
		T* newComponent(new T(std::forward<TArgs>(args)...));

		newComponent->owner = this;
		
		_components.emplace_back(newComponent);
		componentTypeMap[&typeid(*newComponent)] = newComponent;

		newComponent->Initialize();
		
		return *newComponent;
	}

	template <typename T>
	T* GetComponent() {
		return static_cast<T*>(componentTypeMap[&typeid(T)]);
	}
};