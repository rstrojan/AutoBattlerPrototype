#pragma once

#include "Decrement.h"


Decrement::Decrement(std::shared_ptr<GameObject> owner)
    : Base_IAbility("Decrement", owner)
    , eventHandler(
        [owner](const std::string& str) {
            //dynamic_pointer_cast<Unit>(owner)->addToStat("durability", -1);
            std::cout << "decrement called\n";
        }
    )
{};