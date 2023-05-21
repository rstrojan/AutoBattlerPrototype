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
// Creates a Mod with the given name, stat, type, value, and owner.
Mod::Mod(std::string name, statType stat, modType type, float value, std::shared_ptr<GameObject> owner)
	: GameObject(name)
{
	this->stat = stat;
	this->type = type;
	this->value = value;
	this->owner = owner;
};

// NOT FOR NORMAL USE, it is here to satisfy cereal. I need a completely blank constructor
// to capture data when loading so I've included this here.
Mod::Mod()
	: GameObject(""),
	stat(),
	type(),
	value(),
	owner()
{};

// Call this with a key to load a Mod from the json archive.
Mod::Mod(std::string key, std::shared_ptr<GameObject> owner)
	: GameObject(key)
{
	Mod modData;
	try
	{
		std::ifstream file("resources/jsonArchives/Mod.json");
		cereal::JSONInputArchive archive(file);
		archive(cereal::make_nvp(key, modData));
	}
	catch (const cereal::Exception& e)
	{
		std::cout << "Error loading Mod: " << e.what() << std::endl;
		std::exit(1);
	}

	this->stat = modData.stat;
	this->type = modData.type;
	this->value = modData.value;
	this->owner = owner;
}


void Mod::save()
{
	std::fstream file;
	file.open("resources/jsonArchives/Mod.json", std::ios::app);
	cereal::JSONOutputArchive archive(file);
	auto const objname = this->name;
	archive(cereal::make_nvp(objname, * this));
}

