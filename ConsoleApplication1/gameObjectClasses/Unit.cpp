#include "Unit.h"

Unit::Unit(std::string name, std::string type, int hitPoints, int attack, int defense)
	: GameObject(name)
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

//Adds an item to one of the three item slots
// depending on the on the item's ENUM itemType.
void Unit::addItem(std::shared_ptr<Item> item)
{
	if (item->type == Item::itemType::WEAPON)
		weapon = item;
	else if (item->type == Item::itemType::ARMOR)
		armor = item;
	else if (item->type == Item::itemType::TRINKET)
		trinket = item;

	generateChoiceDetailString();
	generateSlotDetailMap();
	return;
}

//Removes an item from one of the three item slots
// depending on the type of item.
// Returns a pointer to the item that was removed.
std::shared_ptr <Item> Unit::removeItem(Item::itemType type)
{
	std::shared_ptr <Item> temp;

	if (type == Item::itemType::WEAPON)
	{
		temp = weapon;
		weapon = NULL;
	}
	else if (type == Item::itemType::ARMOR)
	{
		temp = armor;
		armor = NULL;
	}
	else if (type == Item::itemType::TRINKET)
	{
		temp = trinket;
		trinket = NULL;
	}

	generateChoiceDetailString();
	generateSlotDetailMap();
	return temp;
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
//The L# (Line Number) keys dictate the order in which they are printed.
void Unit::generateSlotDetailMap()
{
	slotDetailMap.clear();
	slotDetailMap["L1"] = name;
	slotDetailMap["L2"] = type;
	slotDetailMap["L3"] = "H:" + std::to_string(hitPoints)
		+ "|A:" + std::to_string(attack) + " |D:" + std::to_string(defense);
	if (weapon != NULL)
		slotDetailMap["L4"] = weapon->name + ": +" + std::to_string(weapon->attackModifier) + "atk";
	if (armor != NULL)
		slotDetailMap["L5"] = armor->name + ": +" + std::to_string(armor->defenseModifier) + "def";
	if (trinket != NULL)
		slotDetailMap["L6"] = trinket->name + ": +" + std::to_string(trinket->hitPointModifier) + "hp";



	return;
}