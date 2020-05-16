#pragma once

struct Entity;

struct Component {
public:
	Entity* owner;
	virtual ~Component() {};
	virtual void Initialize() {};
	virtual void Update(float deltaTime) {};
	virtual void Render() {};
}; 