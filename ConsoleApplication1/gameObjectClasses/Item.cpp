#include "Item.h"

Item::Item(
	  std::string name
	, std::string type
	, int durability
	, std::vector<std::shared_ptr<Mod>> modList
)
	: GameObject(name)
	, type(type)
	, durability(durability)
	, modList(modList)
{
	generateChoiceDetailString();
}

//Keyword constructor that loads a given key from the json archive
Item::Item(std::string key)
	: GameObject(key)
	, type()
	, durability()
	, modList() 
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

	this->durability       = itemData.durability;
	this->type             = itemData.type;

	for (auto const x : itemData.modKeyList)
	{
		modList.emplace_back(std::make_shared<Mod>(x, std::make_shared<GameObject>(*this)));
	}
	for (auto const x : itemData.tagKeyList)
	{
		tags.emplace(std::make_pair(x,std::make_shared<GameObject>(*this)));
	}

	generateChoiceDetailString();
}

//Creates or updates a string of key details of the 
// object for use as a choice in a Prompt.
void Item::generateChoiceDetailString()
{
	choiceDetailString = name + "; " + type + "; " + std::to_string(durability);

	for (auto const& x : modList)
	{
		choiceDetailString += "; " + x->name;
	}

	return;
}

// NOT FOR NORMAL USE, this is for making a blank item for cereal
Item::Item()
	: GameObject("")
	, type()
	, durability()
	, modList()
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