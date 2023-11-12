#pragma once

#include <memory>
#include "../../gameObjectClasses/Base_IAbility.h"
#include "../IAbility.h"
#include "../IAbilityFactory.h"
#include "../../sys/Events.h"


class Decrement : public Base_IAbility, public IAbility
{
public:
    Events::event_handler<const std::string&> eventHandler;

    Decrement(std::shared_ptr<GameObject> owner)
        : Base_IAbility("Decrement", owner)
        , eventHandler(
                [owner](const std::string& str) {
                    //dynamic_pointer_cast<Unit>(owner)->addToStat("durability", -1);
                    std::cout << "decrement called\n";
                }
        )
    {};

    void update(GS_Campaign& currGS) {
     //currGS.Decrement.remove_id(eventHandler.id());
     //currGS.Decrement.add(eventHandler);
 };

};


class DecrementFactory : public IAbilityFactory
{
public:
    Events::event_handler<> eventHandler;

    static std::shared_ptr<IAbility> makeIAbility(std::shared_ptr<GameObject> owner)
    {
        return std::make_shared<Decrement>(owner);
    };

};