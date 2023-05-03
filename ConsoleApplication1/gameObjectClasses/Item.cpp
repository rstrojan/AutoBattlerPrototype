#include "Item.h"

Item::Item(std::string name, itemType type, int durability, int hitPointModifier, int attackModifier, int defenseModifier,
	std::vector<std::string> modKeys)
	: GameObject(name)
{
	this->name = name;
	this->type = type;
	this->durability = durability;
	this->hitPointModifier = hitPointModifier;
	this->attackModifier = attackModifier;
	this->defenseModifier = defenseModifier;
	//for the constructur, I need getEntry working. If anything ever needs child object,
	// it will a string or list to be used in a getEntryConstructor that all objects will have.
	
	//this modlist thing is temporary! I'm justy trying it out for testing.
	modList.emplace_back(Mod("mod1", Mod::statType::HITPOINTS, Mod::modType::ADD, 5, std::shared_ptr<GameObject>(this)));
}