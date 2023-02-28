#pragma once
#include <map>
#include <string>
#include <vector>

class GS_Campaign
{
	GS_Campaign();

public:
	std::map <std::string, std::string> prepLoopConsumableInv;
	std::map <std::string, std::string> prepLoopEquipmentInv;
	std::vector <std::string> prepLoopUnitInv;
};

