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
#include "..\gameObjectClasses\Rule.h"
#include "..\gameObjectClasses\RuleSet.h"

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
	static void feedVanguard(Player& p);
	static void swapItemsInDetailInv(Inventory& inv);
	static void manageUnitMenu(Player& p);
	static void equipUnitMenu(Player& p);
	static void feedUnitMenu(Player& p);
	static bool multiTagCheck(GameObject& obj, RuleSet& ruleSet);
	static bool tagCheck(GameObject& obj, Rule rule);

	void prepLoop();
	void preCombatLoop();
};

