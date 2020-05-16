#pragma once
#include <vector>
#include "Entity.h"

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
