#pragma once
#include <vector>
#include <string>
#include <map>
#include <memory>

#include "..\sys\Prompt.h"
#include "..\sys\PrntScrn.h"
#include "GS_Campaign.h"
#include "..\Inventory.h"
#include "..\gameObjectClasses\GameObject.h"
#include "..\gameObjectClasses\Player.h"

class GM_Campaign
{
private:
	Player p;
	GS_Campaign gs;
	Prompt userPrompt;
	PrntScrn ps;

public:
	GM_Campaign();

	static void chooseFromQuantityInv(std::string promptKey, Inventory& fromInv, Inventory& toInv);
	static void chooseFromDetailInv(std::string promptKey, Inventory& fromInv, Inventory& toInv);
	static void removeFromDetailInv(Inventory& fromInv);
	static void equipVanguard(Player& p, std::string action);
	static void swapItemsInDetailInv(Inventory& inv);
	static void manageUnitMenu(Player& p);
	static void equipUnitMenu(Player& p);

	void prepLoop();
	void preCombatLoop();
};

