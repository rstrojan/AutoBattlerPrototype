#pragma once
#include <map>
#include <string>
#include <vector>
#include "../gameObjectClasses/GameObject.h"
#include "../gameObjectClasses/Unit.h"
#include "../gameObjectClasses/Item.h"
#include "../gameObjectClasses/Consumable.h"
#include "../Inventory.h"
#include "../sys/Events.h"

class GS_Campaign
{


public:
	GS_Campaign();
	Inventory prepLoopConsumablesInv;
	Inventory prepLoopEquipmentInv;
	Inventory prepLoopUnitInv;
	Events::event<const std::string&> Decrement;


private:

};

