#include "Inventory.h"


Inventory::Inventory(std::string name)
{
	this->name = name;
	updateQuantityMap();
	updateDetailedChoiceVector();
}

//Adds a pointer to an obj quantity times.
//Note that this adds multiple pointers to the same obj
// not new objs.
void Inventory::addItem(GameObject* obj, int quantity)
{
	for (int i = 0; i < quantity; i++)
	{
		inv.push_back(obj);
	}
	updateQuantityMap();
	return;
}

//Remove a Game Object, based on obj pointer.
void Inventory::removeItem(GameObject* obj)
{
	for (auto i = begin(inv); i != end(inv);)
	{
		if (*i == obj)
		{
			i = inv.erase(i);
			updateQuantityMap();
			return;
		}
		else
			++i;
	}
	return;
}

//Remove a Game Object based on the "name" property of the obj.
void Inventory::removeItem(std::string itemName)
{
	for (auto i = begin(inv); i != end(inv);)
	{
		if ((*i)->name == itemName)
		{
			i = inv.erase(i);
			updateQuantityMap();
			return;
		}
		else
			++i;
	}
	return;
}

//Creates or Updates a Quantity Map, which is a map<string, string>
// where the key is an obj name and the value is the number of 
// instances of that obj in the given inventory. The value is kept as
// a string so that it is easy to pass into a PrntScrn slot.
void Inventory::updateQuantityMap()
{
	quantityMap.clear();
	quantityMap["title"] = name; //name of the inventory

	for (auto const& item : inv)
	{
		if (quantityMap.count(item->name) != 0)
		{
			int x = std::stoi(quantityMap[item->name]);
			x += 1;
			quantityMap[item->name] = std::to_string(x);
		}
		else
		{
			quantityMap[item->name] = "1";
		}
	}
	return;
}

//Takes string matching a GameObject name or choiceDetailString, and searches for it in the 
// fromInv. If found, it adds a copy of the pointer to the toInv and then
// removes the pointer from the fromInv.
void Inventory::transferItem(std::string itemName,
	Inventory& fromInv, Inventory& toInv)
{
	for (auto i = begin(fromInv.inv); i != end(fromInv.inv);)
	{
		if ((*i)->name == itemName)
		{
			toInv.addItem(*i);
			fromInv.removeItem(*i);
			return;
		}
		else if ((*i)->getChoiceDetailString() == itemName)
		{
			toInv.addItem(*i);
			fromInv.removeItem(*i);
			return;
		}
		else
			++i;
	}
	return;
}

//Returns a detailedChoiceVector of strings for use with the Prompt
// class. Each string equates to a GameObject in the inv and some of
// it's key details based on that GameObjects choiceDetailString.
std::vector<std::string>& Inventory::getDetailedChoiceVector()
{
	updateDetailedChoiceVector();
	return detailedChoiceVector;
}

//Creates or updates a detailedChoiceVector of strings for use with the Prompt class.
void Inventory::updateDetailedChoiceVector()
{
	detailedChoiceVector.clear();
	for (auto const& item : inv)
	{
		detailedChoiceVector.push_back(item->getChoiceDetailString());
	}
}

//Returns a quantityChoiceVector of strings for use with the Prompt
// class. Each string equates to a different GameObject "name" and the value
// equates to the number of instances of objs that share that name.
std::vector<std::string>& Inventory::getQuantityChoiceVector()
{
	updateQuantityChoiceVector();
	return quantityChoiceVector;
}

//Creates or updates a quantityChoiceVector of strings for use with the Prompt class.
void Inventory::updateQuantityChoiceVector()
{
	quantityChoiceVector.clear();

	for (auto const& x : quantityMap)
	{
		if (x.first != "title")
			quantityChoiceVector.push_back(x.first);
	} 
}

//Returns a list of detail maps based on the objs in inv. The 'title' of the detail map
//will be overwritten with a value indicating it's position
std::vector<std::map<std::string, std::string>>& Inventory::getSlotDetailMaps()
{
	updateSlotDetailMaps();
	return slotDetailMaps;
}

//Creates or updates a list of detail maps based on the objs in the inv.
// This where the 'title' of the detail map will be overwritten with position data
void Inventory::updateSlotDetailMaps()
{
	slotDetailMaps.clear();
	int pos = 1;
	for (auto const& item : inv)
	{
		std::map<std::string, std::string> tempMap = item->getSlotDetailMap();
		tempMap["title"] = "Pos " + std::to_string(pos);
		slotDetailMaps.push_back(tempMap);
		pos++;
	}
}
