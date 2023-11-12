#pragma once
#include <memory>
#include "../gameObjectClasses/GameObject.h"
#include "../gameObjectClasses/Base_IAbility.h"
#include "../gameObjectClasses/Unit.h"
#include "../interfaceClasses/IAbility.h"
#include "../modeAndStateClasses/GS_Campaign.h"
#include "../interfaceClasses/IAbilityFactory.h"
#include "../interfaceClasses/IAbilityClasses/Decrement.h"


class IAbilityDirector
{
public:

    static std::shared_ptr<IAbility> getIAbility(
          std::string key
        , std::shared_ptr<GameObject> owner)
    {
        if (key == "Decrement")
        {
            return DecrementFactory::makeIAbility(owner);
        }
        return std::shared_ptr<IAbility>(nullptr);
    }

};

