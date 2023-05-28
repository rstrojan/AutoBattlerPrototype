#include "Item.h"

Item::Item(std::string name, itemType type, int durability, int hitPointModifier, int attackModifier, int defenseModifier,
	std::vector<std::shared_ptr<Mod>> modList)
	: GameObject(name)
{
	this->name = name;
	this->type = type;
	this->durability = durability;
	this->hitPointModifier = hitPointModifier;
	this->attackModifier = attackModifier;
	this->defenseModifier = defenseModifier;
	this->modList = modList;
}

//Keyword constructor that loads a given key from the json archive
Item::Item(std::string key)
	: GameObject(key),
	type(),
	hitPointModifier(),
	attackModifier(),
	defenseModifier(),
	durability(),
	modList()
{
	Item itemData;
	try 
	{
		std::ifstream file("resources/jsonArchives/Item.json");
		cereal::JSONInputArchive archive(file);
		archive(cereal::make_nvp(key, itemData));
	}
	catch (const cereal::Exception& e)
	{
		std::cout << "Error loading Item: " << e.what() << std::endl;
		std::exit(1);
	}

	this->hitPointModifier = itemData.hitPointModifier;
	this->attackModifier = itemData.attackModifier;
	this->defenseModifier = itemData.defenseModifier;
	this->durability = itemData.durability;
	this->type = itemData.type;

	for (auto const x : itemData.modKeyList)
	{
		modList.emplace_back(std::make_shared<Mod>(x, std::make_shared<GameObject>(*this)));
	}

	for (auto const x : itemData.tagKeyList)
	{
		tags.emplace(std::make_pair(x,std::make_shared<GameObject>(*this)));
	}

	for (auto mod : modList)
	{
		if (mod->stat == Mod::HITPOINTS)
			hitPointModifier = (int)std::ceil(mod->value);
		else if (mod->stat == Mod::DEFENSE)
			defenseModifier = (int)std::ceil(mod->value);
		else if (mod->stat == Mod::ATTACK)
			attackModifier = (int)std::ceil(mod->value);
	}

}

// NOT FOR NORMAL USE, this is for making a blank item for cereal
Item::Item()
	: GameObject(""),
	type(),
	hitPointModifier(),
	attackModifier(),
	defenseModifier(),
	durability(),
	modList()
{}
// NOT FOR NORMAL USE, this is for saving an item to json with cereal
void Item::save()
{
	std::fstream file;
	file.open("resources/jsonArchives/Item.json", std::ios::app);
	cereal::JSONOutputArchive archive(file);
	auto const objname = this->name;
	archive(cereal::make_nvp(objname, * this));
}