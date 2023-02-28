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

	static void chooseFromInv(std::string promptKey, std::map <std::string, std::string> &fromInv,
								std::map <std::string, std::string> &toInv);
	static void chooseFromQuantityInv(std::string promptKey, Inventory& fromInv, Inventory& toInv);
	static void chooseFromDetailInv(std::string promptKey, Inventory& fromInv, Inventory& toInv);
	static void chooseUnit(std::vector <std::string> fromInv, std::vector<std::string> toInv);

	static void prepLoop();
};

