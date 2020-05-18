#include "InteractionManager.h"

InteractionManager::InteractionManager()
{
    
}

void InteractionManager::HandleInteractions(){
    for(auto& interaction: interactionQueue){
        if (interaction->intTag == PLAYER_TO_OBJECT) {
            
        }
    }
    ClearInteractionQueue();
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