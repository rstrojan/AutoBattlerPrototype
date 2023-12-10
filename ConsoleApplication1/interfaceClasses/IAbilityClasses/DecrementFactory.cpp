#pragma once

#include "DecrementFactory.h"


std::shared_ptr<IAbility> DecrementFactory::makeIAbility(std::shared_ptr<GameObject> owner)
{
    return std::make_shared<Decrement>(owner);
}