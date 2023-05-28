#include "GameObject.h"

GameObject::GameObject(std::string name)
	: tags()
{
	this->name = name;
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

//Adds the given list of tags to the object.
void GameObject::addTags(std::multimap<std::string, std::shared_ptr<GameObject>> tagsToAdd)
{
	for (auto tagToAdd : tagsToAdd)
	{
		tags.insert(tagToAdd);
	}
	return;
}

//Removes tags that match the given list of tags.
void GameObject::removeTags(std::multimap<std::string, std::shared_ptr<GameObject>> tagsToRemove)
{
	for (auto tagToRemove = begin(tagsToRemove); tagToRemove != end(tagsToRemove);)
	{
		for (auto tag = begin(tags); tag != end(tags);)
		{
			if (tag->first == tagToRemove->first && tag->second == tagToRemove->second)
			{
				tags.erase(tag);
				break;
			}
			else
				++tag;
		}
		++tagToRemove;

	}
	return;
}

//Returns the number of tags that match the given tag.
int GameObject::tagCount(std::string tag)
{
	return tags.count(tag);
}


//NOT FOR NORMAL USE, this is for the cereal library
// to use to create a json archive of the object.
GameObject::GameObject()
	: tags()
{
	name = "default";
	generateChoiceDetailString();
	generateSlotDetailMap();
}
//NOT FOR NORMAL USE, this is to save an object to a json archive
//for use as a template.
void GameObject::save()
{
	std::ofstream file("resources/jsonArchives/GameObject.json");
	cereal::JSONOutputArchive archive(file);
	archive(*this);
}

