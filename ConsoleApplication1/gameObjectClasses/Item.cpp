#include "Item.h"

Item::Item(std::string name, itemType type, int durability, int hitPointModifier, int attackModifier, int defenseModifier)
	: GameObject(name)
{
	this->name = name;
	this->type = type;
	this->durability = durability;
	this->hitPointModifier = hitPointModifier;
	this->attackModifier = attackModifier;
	this->defenseModifier = defenseModifier;
}