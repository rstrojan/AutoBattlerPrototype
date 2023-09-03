#pragma once
#include <map>
#include <string>
#include <vector>
#include "../gameObjectClasses/GameObject.h"
#include "../gameObjectClasses/Unit.h"
#include "../gameObjectClasses/Item.h"
#include "../gameObjectClasses/Consumable.h"
#include "../Inventory.h"

class GS_Campaign
{


public:
	GS_Campaign();
	Inventory prepLoopConsumablesInv;
	Inventory prepLoopEquipmentInv;
	Inventory prepLoopUnitInv;

private:

};

