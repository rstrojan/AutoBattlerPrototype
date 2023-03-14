#include "Unit.h"

Unit::Unit(std::string name, std::string type, int hitPoints, int attack, int defense) : GameObject(name)
{
	this->name = name;
	this->type = type;
	this->hitPoints = hitPoints;
	this->attack = attack;
	this->defense = defense;
	weapon = NULL;
	armor = NULL;
	trinket = NULL;
}

//Creates or updates a string of key details of the 
// object for use as a choice in a Prompt.
void Unit::generateChoiceDetailString()
{
	choiceDetailString = name + "(" + type + ")|H:" + std::to_string(hitPoints) 
						+ "|A:" + std::to_string(attack) + "|D:" + std::to_string(defense);
	return;
}

//Creates or updates a reference of a map<string, string> that has
// key details about the object for use in a PrntScrn slot.
void Unit::generateSlotDetailMap()
{
	slotDetailMap.clear();
	if (trinket != NULL)
		slotDetailMap["T"] = trinket->name;
	if (armor != NULL)
		slotDetailMap["A"] = armor->name;
	if (weapon != NULL)
		slotDetailMap["W"] = weapon->name;
	slotDetailMap["stats"] = "H:" + std::to_string(hitPoints)
					+ "|A:" + std::to_string(attack) + " |D:" + std::to_string(defense);
	slotDetailMap["type"] = type;
	slotDetailMap["N"] = name;
	return;
}