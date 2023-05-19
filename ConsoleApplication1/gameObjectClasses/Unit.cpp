#include "Unit.h"

Unit::Unit(std::string name, std::string type, int baseHitPoints, int baseAttack, int baseDefense)
    : GameObject(name),
    weaponKey(),
    armorKey(),
    trinketKey(),
    modKeyList()
{
    this->type = type;
    this->baseHitPoints = baseHitPoints;
    this->baseAttack = baseAttack;
    this->baseDefense = baseDefense;
    weapon = NULL;
    armor = NULL;
    trinket = NULL;
}

// NOT FOR NORMAL USE, this is for making a blank unit for cereal
Unit::Unit() 
    : GameObject("")
{}

//Takes a key and loads the unit from the Unit.json file
Unit::Unit(std::string key)
    : GameObject(key)
{
    std::ifstream file("resources/jsonArchives/Unit.json");
    cereal::JSONInputArchive archive(file);
    Unit unitData;
    archive(cereal::make_nvp(key, unitData));
    this->baseHitPoints = unitData.baseHitPoints;
    this->baseAttack = unitData.baseAttack;
    this->baseDefense = unitData.baseDefense;
    this->type = unitData.type;
    if (!unitData.weaponKey.empty())
        this->weapon = std::make_shared<Item>(unitData.weaponKey);
    if (!unitData.armorKey.empty())
        this->addItem(std::make_shared<Item>(unitData.armorKey));
    if (!unitData.trinketKey.empty())
        this->addItem(std::make_shared<Item>(unitData.trinketKey));
    //for (auto const x : unitData.modKeyList)
    //    this->modList.push_back(std::make_shared<Mod>(x));
}

void Unit::save()
{
    std::fstream file;
    file.open("resources/jsonArchives/Unit.json", std::ios::app);
    cereal::JSONOutputArchive archive(file);
    auto const objname = this->name;
    archive(cereal::make_nvp(objname, *this));
}

//Adds an item to one of the three item slots
// depending on the on the item's ENUM itemType.
void Unit::addItem(std::shared_ptr<Item> item)
{
    if (item->type == Item::itemType::WEAPON)
        weapon = item;
    else if (item->type == Item::itemType::ARMOR)
        armor = item;
    else if (item->type == Item::itemType::TRINKET)
        trinket = item;

    addMods(item->modList);
    updateMods();
    generateChoiceDetailString();
    generateSlotDetailMap();
    return;
}

//Removes an item from one of the three item slots
// depending on the type of item.
// Returns a pointer to the item that was removed.
std::shared_ptr <Item> Unit::removeItem(Item::itemType type)
{
    std::shared_ptr <Item> temp;

    if (type == Item::itemType::WEAPON && weapon != NULL)
    {
        temp = weapon;
        weapon = NULL;
        removeMods(temp->modList);

    }
    else if (type == Item::itemType::ARMOR && armor != NULL)
    {
        temp = armor;
        armor = NULL;
        removeMods(temp->modList);

    }
    else if (type == Item::itemType::TRINKET && trinket != NULL)
    {
        temp = trinket;
        trinket = NULL;
        removeMods(temp->modList);

    }

    updateMods();
    generateChoiceDetailString();
    generateSlotDetailMap();
    return temp;
}

int Unit::addMods(std::vector<Mod>& modList)
{
    for (auto mod : modList)
    {
        this->modList.push_back(std::make_shared<Mod>(mod));
    }
    return 0;
}

int Unit::removeMods(std::vector<Mod>& modList)
{
    for (auto modToRemove : modList)
    {
        for (auto i = begin(this->modList); i != end(this->modList);)
        {
            if (modToRemove.owner == (*i)->owner)
            {
                i = this->modList.erase(i);
                break;
            }
            else
                ++i;
        }
    }
    return 0;
}

int Unit::updateMods()
{
    modHitPoints = baseHitPoints;
    modAttack = baseAttack;
    modDefense = baseDefense;

    for (auto mod : modList)
    {
        if (mod->type == Mod::ADD)
        {
            if (mod->stat == Mod::HITPOINTS)
                modHitPoints += mod->value;
            else if (mod->stat == Mod::ATTACK)
                modAttack += mod->value;
            else if (mod->stat == Mod::DEFENSE)
                modDefense += mod->value;
        }
    }

    float modHitPointsAddVal = float(modHitPoints);
    float modAttackAddVal = float(modAttack);
    float modDefenseAddVal = float(modDefense);

    for (auto mod : modList)
        if (mod->type == Mod::MULTIPLY)
        {
            if (mod->stat == Mod::HITPOINTS)
                modHitPoints += (modHitPointsAddVal * mod->value);
            else if (mod->stat == Mod::ATTACK)
                modAttack += (modAttackAddVal * mod->value);
            else if (mod->stat == Mod::DEFENSE)
                modDefense += (modDefenseAddVal * mod->value);
        }
    return 0;
}

//Creates or updates a string of key details of the 
// object for use as a choice in a Prompt.
void Unit::generateChoiceDetailString()
{
    updateMods();
    choiceDetailString = name + "(" + type + ")|H:" + std::to_string(modHitPoints) 
                        + "|A:" + std::to_string(modAttack) + "|D:" + std::to_string(modDefense);
    return;
}

//Creates or updates a reference of a map<string, string> that has
// key details about the object for use in a PrntScrn slot.
//The L# (Line Number) keys dictate the order in which they are printed.
void Unit::generateSlotDetailMap()
{
    slotDetailMap.clear();
    slotDetailMap["L1"] = name;
    slotDetailMap["L2"] = type;
    slotDetailMap["L3"] = "H:" + std::to_string(modHitPoints)
        + "|A:" + std::to_string(modAttack) + " |D:" + std::to_string(modDefense);
    if (weapon != NULL)
        slotDetailMap["L4"] = weapon->name + ": +" + std::to_string(weapon->attackModifier) + "atk";
    if (armor != NULL)
        slotDetailMap["L5"] = armor->name + ": +" + std::to_string(armor->defenseModifier) + "def";
    if (trinket != NULL)
        slotDetailMap["L6"] = trinket->name + ": +" + std::to_string(trinket->hitPointModifier) + "hp";



    return;
}

