#include "InteractionManager.h"

InteractionManager::InteractionManager()
{
    
}

void InteractionManager::HandleInteractions(){
    for(auto& interaction: interactionQueue){
        if (interaction->intTag == PLAYER_TO_OBJECT) {
            auto x = 0.f;
            auto y = 0.f;
            switch (interaction->srcObj.facingDirection) {
            case FacingDirection::FACING_RIGHT:
                x = 10.f;
                break;
            case FacingDirection::FACING_LEFT:
                x = -10.f;
                break;
            case FacingDirection::FACING_UP:
                y = -10.f;
                break;
            case FacingDirection::FACING_DOWN:
                y = 10.f;
                break;
            }

            interaction->targObj.GetComponent<TransformComponent>()->position.x += x;
            interaction->targObj.GetComponent<TransformComponent>()->position.y += y;
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