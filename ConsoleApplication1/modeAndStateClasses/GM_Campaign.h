#pragma once
#include <map>
#include <string>
#include <vector>

#include "..\sys\Prompt.h"
#include "..\sys\PrntScrn.h"
#include "GS_Campaign.h"
#include "..\Inventory.h"
#include "..\gameObjectClasses\GameObject.h"
#include "..\gameObjectClasses\Player.h"

class GM_Campaign
{

public:
	GM_Campaign();

	static void chooseFromQuantityInv(std::string promptKey, Inventory& fromInv, Inventory& toInv);
	static void chooseFromDetailInv(std::string promptKey, Inventory& fromInv, Inventory& toInv);

	static void prepLoop();
};

