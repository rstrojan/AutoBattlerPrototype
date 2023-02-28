#include "Inventory.h"


Inventory::Inventory(std::string name)
{
	this->name = name;
	updateQuantityMap();
	updateDetailedChoiceVector();
}

void Inventory::addItem(GameObject* obj, int quantity)
{
	for (int i = 0; i < quantity; i++)
	{
		inv.push_back(obj);
	}
	updateQuantityMap();
	return;
}

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

void Inventory::updateQuantityMap()
{
	quantityMap.clear();
	quantityMap["title"] = name;

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

std::vector<std::string>& Inventory::getDetailedChoiceVector()
{
	updateDetailedChoiceVector();
	return detailedChoiceVector;
}

void Inventory::updateDetailedChoiceVector()
{
	detailedChoiceVector.clear();
	for (auto const& item : inv)
	{
		detailedChoiceVector.push_back(item->getChoiceDetailString());
	}
}

std::vector<std::string>& Inventory::getQuantityChoiceVector()
{
	updateQuantityChoiceVector();
	return quantityChoiceVector;
}

void Inventory::updateQuantityChoiceVector()
{
	quantityChoiceVector.clear();

	for (auto const& x : quantityMap)
	{
		if (x.first != "title")
			quantityChoiceVector.push_back(x.first);
	} 
}

//returns a list of detail maps based on the objs in inv. The 'title' of the detail map
//will be overwritten with a value indicating it's position
std::vector<std::map<std::string, std::string>>& Inventory::getSlotDetailMaps()
{
	updateSlotDetailMaps();
	return slotDetailMaps;
}

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