#pragma once

#include <memory>
#include "../../gameObjectClasses/Base_IAbility.h"
#include "../IAbility.h"

class Decrement : public Base_IAbility, public IAbility
{
public:
    Events::event_handler<const std::string&> eventHandler;

    Decrement(std::shared_ptr<GameObject> owner);

    void update(GS_Campaign& currGS) {
     //currGS.Decrement.remove_id(eventHandler.id());
     //currGS.Decrement.add(eventHandler);
    };

    std::string getName() {
		return this->name;
	};

};


