#pragma once
#include <vector>
#include "Constants.h"
#include "Entity.h"
struct Entity;

struct InteractionEvent {
	Entity& srcObj;
	Entity& targObj;
	InteractionTag intTag;
};

struct InteractionManager {
	InteractionManager();
	std::vector<InteractionEvent*>interactionQueue;
	void HandleInteractions();
	void ClearInteractionQueue();
};
