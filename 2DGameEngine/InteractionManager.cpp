#include "InteractionManager.h"

void InteractionManager::HandleInteractions(){
    for(auto& interaction: interactionQueue){

    }
}

void InteractionManager::ClearInteractionQueue(){
    if (interactionQueue.size() > 0)
    {
        for (auto ie : interactionQueue)
        {
            delete ie;
        }

        interactionQueue.clear();
    }
}