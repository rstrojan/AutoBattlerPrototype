#include "Mod.h"
//
//Mod::Mod(std::string name, statType stat, modType type, float value, std::shared_ptr<GameObject> owner)
//    : GameObject(name)
//{
//    this->stat = stat;
//    this->type = type;
//    this->value = value;
//    this->owner = owner;
//}

Mod::Mod(std::string name, statType stat, modType type, float value, std::shared_ptr<GameObject> owner)
	: GameObject(name)
{
	this->stat = stat;
	this->type = type;
	this->value = value;
	this->owner = owner;
};