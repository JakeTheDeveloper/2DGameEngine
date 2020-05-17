#pragma once
#include <vector>
#include "Constants.h"
#include "Entity.h"
#include "Constants.h"
struct Entity;

struct InteractionEvent {
	InteractionEvent(Entity& sObj, Entity& tObj, InteractionTag intTag)
		: srcObj(sObj), targObj(tObj), intTag(intTag) {
	};
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
