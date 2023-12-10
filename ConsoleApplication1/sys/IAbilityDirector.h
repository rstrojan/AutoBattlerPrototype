#pragma once
#include <memory>
#include "../interfaceClasses/IAbility.h"
#include "../interfaceClasses/IAbilityClasses/DecrementFactory.h"


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

