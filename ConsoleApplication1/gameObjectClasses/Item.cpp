#include "Item.h"

Item::Item(std::string name, itemType type, int durability, int hitPointModifier, int attackModifier, int defenseModifier,
	std::vector<Mod> modList)
	: GameObject(name)
{
	this->name = name;
	this->type = type;
	this->durability = durability;
	this->hitPointModifier = hitPointModifier;
	this->attackModifier = attackModifier;
	this->defenseModifier = defenseModifier;
	this->modList = modList;
	//for the constructur, I need getEntry working. If anything ever needs child object,
	// it will a string or list to be used in a getEntryConstructor that all objects will have.
	
	//this modlist thing is temporary! I'm justy trying it out for testing.
	//modList.emplace_back(Mod("mod1", Mod::statType::HITPOINTS, Mod::modType::ADD, 5, std::shared_ptr<GameObject>(this)));
}

Item::Item()
	: GameObject("")
{
}

Item::Item(std::string key)
	: GameObject(key)
{
	std::ifstream file("resources/jsonArchives/Item.json");
	cereal::JSONInputArchive archive(file);
	Item itemData;
	archive(cereal::make_nvp(key, itemData));
	this->hitPointModifier = itemData.hitPointModifier;
	this->attackModifier = itemData.attackModifier;
	this->defenseModifier = itemData.defenseModifier;
	this->durability = itemData.durability;
	this->type = itemData.type;

	for (auto const x : itemData.modKeyList)
	{
		modList.emplace_back(Mod(x, std::make_shared<GameObject>(*this)));
	}

	for (auto mod : modList)
	{
		if (mod.stat == Mod::HITPOINTS)
			hitPointModifier = mod.value;
		else if (mod.stat == Mod::DEFENSE)
			defenseModifier = mod.value;
		else if (mod.stat == Mod::ATTACK)
			attackModifier = mod.value;
	}

}

void Item::save()
{
	std::fstream file;
	file.open("resources/jsonArchives/Item.json", std::ios::app);
	cereal::JSONOutputArchive archive(file);
	auto const objname = this->name;
	//modKeyList.clear();
	//for (auto const x : modList)
	//{
	//	modKeyList.push_back(x.name);
	//}
	archive(cereal::make_nvp(objname, * this));
}