#include "GameObject.h"


GameObject::GameObject(std::string name)
{
	this->name = name;
	generateChoiceDetailString();
	generateSlotDetailMap();
}

std::string GameObject::getChoiceDetailString()
{
	generateChoiceDetailString();
	return choiceDetailString;
}

void GameObject::generateChoiceDetailString()
{
	choiceDetailString = name;
	return;
}

std::map<std::string, std::string>& GameObject::getSlotDetailMap()
{
	generateSlotDetailMap();
	return slotDetailMap;
}

void GameObject::generateSlotDetailMap()
{
	slotDetailMap.clear();
	slotDetailMap["N"] = name;
	return;
}