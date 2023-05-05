#include "Inventory.h"


Inventory::Inventory(std::string name)
{
    this->name = name;
    maxSize = NULL;
    updateQuantityMap();
    updateDetailedChoiceVector();
}

Inventory::Inventory(std::string name, int maxSize)
{
    setMaxSize(maxSize);
    this->name = name;
    updateQuantityMap();
    updateDetailedChoiceVector();
}

//returns true if maxSize is set
bool Inventory::hasMaxSize()
{
    if (maxSize == NULL)
        return false;
    else
        return true;
}

//returns true if the inv is empty, else returns false
bool Inventory::isEmpty()
{
    if (inv.size() == 0)
        return true;
    else
        return false;
}

//returns true if the inv is full, else returns false
bool Inventory::isFull()
{
    if (maxSize != NULL)
    {
        if (inv.size() == maxSize)
            return true;
        else
            return false;
    }
    return false;
}


//sets maxSize to size, and hasMaxSize to true
//returns maxSize
int Inventory::setMaxSize(int size)
{
    maxSize = size;
    return maxSize;
}

//returns the maxSize of the inventory
int Inventory::getMaxSize()
{
    return maxSize;
}

//returns current size of the inventory
int Inventory::getCurrSize()
{
    return inv.size();
}

//sets maxSize to NULL
void Inventory::clearSize()
{
    maxSize = NULL;
    return;
}

//Adds a pointer to an obj quantity times.
//Note that this adds multiple pointers to the same obj
// not new objs.
void Inventory::addItem(std::shared_ptr<GameObject> obj, int quantity)
{
    for (int i = 0; i < quantity && !isFull(); i++)
    {
        inv.push_back(obj);
    }
    updateQuantityMap();
    return;
}

//Remove a Game Object from an inventory, based on obj pointer.
// Returns a Game Object pointer to the removed object.
// If no object is found, returns NULL.
std::shared_ptr<GameObject> Inventory::removeItem(std::shared_ptr<GameObject> obj)
{
    if (!isEmpty())
    {
        for (auto i = begin(inv); i != end(inv);)
        {
            if (*i == obj)
            {
                obj = *i;
                i = inv.erase(i);
                updateQuantityMap();
                return obj;
            }
            else
                ++i;
        }
    }
    return NULL;
}

//Remove a Game Object based on the "name" property of the obj.
// Returns a Game Object pointer to the removed object.
// If no object is found, returns NULL.
std::shared_ptr<GameObject> Inventory::removeItem(std::string itemName)
{
    std::shared_ptr<GameObject> obj;
    if (!isEmpty())
    {
        for (auto i = begin(inv); i != end(inv);)
        {
            if ((*i)->name == itemName || (*i)->getChoiceDetailString() == itemName)
            {
                obj = *i;
                i = inv.erase(i);
                updateQuantityMap();
                return obj;
            }
            else
                ++i;
        }
    }
    return NULL;
}

//Takes string matching a GameObject name or choiceDetailString, and searches for it in the 
// fromInv. If found, it adds a copy of the pointer to the toInv and then
// removes the pointer from the fromInv.
void Inventory::transferItem(std::string itemName,
    Inventory& fromInv, Inventory& toInv)
{
    if (!toInv.isFull() && !fromInv.isEmpty())
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

//Takes two int values, and swaps the pointers to the objs at those positions.
//Note that this does not swap the actual objs, just the pointers to them.
void Inventory::swapItems(int pos1, int pos2)
{
    if (pos1 > 0 && pos1 <= inv.size() && pos2 > 0 && pos2 <= inv.size())
    {
        std::shared_ptr<GameObject> temp = inv[pos1 - 1];
        inv[pos1 - 1] = inv[pos2 - 1];
        inv[pos2 - 1] = temp;
    }
    return;
}