#pragma once
#include <map>
#include <string>
#include <vector>
#include "../gameObjectClasses/GameObject.h"
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

