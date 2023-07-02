#include "Buff.h"

Buff::Buff(std::string name, int durability, std::vector<std::shared_ptr<Mod>> modList, std::vector<std::shared_ptr<GameObject>> abilityList)
	: GameObject(name),
	durability(durability),
	modList(modList),
	abilityList(abilityList)
	{}

//Takes a key and loads the object from the json archive.
Buff::Buff(std::string key)
	: GameObject(key),
	durability(),
	modList(),
	abilityList()
{
	Buff buffData;
	try
	{
		std::fstream file;
		file.open("resources/jsonArchives/Buff.json");
		cereal::JSONInputArchive archive(file);
		archive(cereal::make_nvp(key, buffData));
	}
	catch (const cereal::Exception& e)
	{
			std::cout << "Error loading Buff: " << e.what() << std::endl;
				std::exit(1);
	}
	for (auto const& mod : buffData.modKeyList)
		modList.emplace_back(std::make_shared<Mod>(mod, std::make_shared<GameObject>(*this)));
	//ability object needs to be updated later once Abilities class is made.
	for (auto const& ability : buffData.abilityKeyList)
		this->abilityList.push_back(std::make_shared<GameObject>(ability));
	for (auto const& tag : buffData.tagKeyList)
		tags.emplace(std::make_pair(tag, std::make_shared<GameObject>(*this)));
	this->durability = buffData.durability;
}

//NOT FOR REGULAR USE, this is for making a blank object for cereal.
Buff::Buff()
	: GameObject(""),
	durability(),
	modList(),
	abilityList()
{}

//NOT FOR REGULAR USE, this is to save off objects to the Buff json archive.
void Buff::save()
{
	std::fstream file;
	file.open("resources/jsonArchives/Buff.json", std::ios::app);
	cereal::JSONOutputArchive archive(file);
	auto const objname = this->name;
	archive(cereal::make_nvp(objname, * this));
}