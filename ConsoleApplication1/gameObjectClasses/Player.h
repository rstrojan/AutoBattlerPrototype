#pragma once
#include <map>
#include <string>
#include <vector>

#include "GameObject.h"
#include "..\Inventory.h"

class Player : GameObject
{
public:
	std::map <std::string, std::string> playerConsumableInv;
	std::vector <std::string> playerVanguard;
	std::vector <std::string> playerUnitInv;
	Inventory equipmentInv = Inventory("My Equipment");
	Inventory consumableInv = Inventory("My Consumables");
	Inventory vanguard = Inventory("Vanguard");
	Inventory reinforcements = Inventory("Reinforcements");

	Player(std::string name);
};

