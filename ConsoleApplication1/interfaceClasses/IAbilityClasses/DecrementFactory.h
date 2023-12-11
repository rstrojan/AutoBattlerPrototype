#pragma once

#include <memory>
#include "../IAbilityFactory.h"
#include "Decrement.h"

class DecrementFactory : public IAbilityFactory
{
public:
    Events::event_handler<> eventHandler;

    static std::shared_ptr<IAbility> makeIAbility(std::shared_ptr<GameObject> owner);

};
