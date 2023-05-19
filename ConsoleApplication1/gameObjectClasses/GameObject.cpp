#include "GameObject.h"


GameObject::GameObject(std::string name)
{
	this->name = name;
	generateChoiceDetailString();
	generateSlotDetailMap();
}

GameObject::GameObject()
{	name = "default";
	generateChoiceDetailString();
	generateSlotDetailMap();
}

//Returns a string of key details of the object
// for use as a choice in a Prompt.
std::string GameObject::getChoiceDetailString()
{
	generateChoiceDetailString();
	return choiceDetailString;
}
//Creates or updates a string of key details of the 
// object for use as a choice in a Prompt.
void GameObject::generateChoiceDetailString()
{
	choiceDetailString = name;
	return;
}

//Returns a reference of map<string, string> that has key
// details about the object for use in a PrntScrn slot.
std::map<std::string, std::string>& GameObject::getSlotDetailMap()
{
	generateSlotDetailMap();
	return slotDetailMap;
}

//Creates or updates a reference of a map<string, string> that has
// key details about the object for use in a PrntScrn slot.
void GameObject::generateSlotDetailMap()
{
	slotDetailMap.clear();
	slotDetailMap["N"] = name;
	return;
}

void GameObject::save()
{
	std::ofstream file("resources/jsonArchives/GameObject.json");
	cereal::JSONOutputArchive archive(file);
	archive(*this);
}

