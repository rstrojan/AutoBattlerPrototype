#include "Unit.h"

Unit::Unit(std::string name, std::string type, int baseHitPoints, int baseAttack, int baseDefense)
    : GameObject(name),
    baseHitPoints(baseHitPoints),
    baseAttack(baseAttack),
    baseDefense(baseDefense),
    type(type),
    weapon(NULL),
    armor(NULL),
    trinket(NULL),
    modHitPoints(0),
    modAttack(0),
    modDefense(0)
{
    updateMods();
    generateChoiceDetailString();
    generateSlotDetailMap();
}

//Takes a key and loads the unit from the Unit.json file
Unit::Unit(std::string key)
    : GameObject(key),
    baseHitPoints(),
    baseAttack(),
    baseDefense(),
    type(),
    weapon(),
    armor(),
    trinket(),
    modHitPoints(),
    modAttack(),
    modDefense()
{

    Unit unitData;
    try
    {
        std::ifstream file("resources/jsonArchives/Unit.json");
        cereal::JSONInputArchive archive(file);
        archive(cereal::make_nvp(key, unitData));
    }
    catch (const cereal::Exception& e)
    {
		std::cout << "Error loading Unit: " << e.what() << std::endl;
        std::exit(1);
	}

    for (auto const& x : unitData.modKeyList)
    	modList.emplace_back(std::make_shared<Mod>(x, std::make_shared<GameObject>(*this)));
    for (auto const &x : unitData.tagKeyList)
        tags.emplace(std::make_pair(x, std::make_shared<GameObject>(*this)));

    this->baseHitPoints = unitData.baseHitPoints;
    this->baseAttack = unitData.baseAttack;
    this->baseDefense = unitData.baseDefense;
    this->type = unitData.type;

    if (!unitData.weaponKey.empty())
        this->addItem(std::make_shared<Item>(unitData.weaponKey));
    if (!unitData.armorKey.empty())
        this->addItem(std::make_shared<Item>(unitData.armorKey));
    if (!unitData.trinketKey.empty())
        this->addItem(std::make_shared<Item>(unitData.trinketKey));

}

//Adds an item to one of the three item slots
// depending on the item's ENUM itemType.
void Unit::addItem(std::shared_ptr<Item> item)
{
    if (item->type == Item::itemType::WEAPON)
        weapon = item;
    else if (item->type == Item::itemType::ARMOR)
        armor = item;
    else if (item->type == Item::itemType::TRINKET)
        trinket = item;

    addMods(item->modList);
    addTags(item->tags);
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
        removeTags(temp->tags);
        removeMods(temp->modList);

    }
    else if (type == Item::itemType::ARMOR && armor != NULL)
    {
        temp = armor;
        armor = NULL;
        removeTags(temp->tags);
        removeMods(temp->modList);

    }
    else if (type == Item::itemType::TRINKET && trinket != NULL)
    {
        temp = trinket;
        trinket = NULL;
        removeTags(temp->tags);
        removeMods(temp->modList);

    }

    updateMods();
    generateChoiceDetailString();
    generateSlotDetailMap();
    return temp;
}

//Adds a buff to the unit's buffList as well as the 
// mods, abilities, and tags of the buff.
void Unit::addBuff(std::shared_ptr<Buff> buff)
{
	buffList.push_back(buff);
	addMods(buff->modList);
	//addAbilities(buff->abilityList);
	addTags(buff->tags);
	updateMods();
	generateChoiceDetailString();
	generateSlotDetailMap();
	return;
}

//Removes a buff from the unit's buffList as well as the
// mods, abilities, and tags of the buff.
std::shared_ptr <Buff> Unit::removeBuff(std::shared_ptr<Buff> buff)
{
    std::shared_ptr<Buff> temp;
    for (auto i = begin(buffList); i != end(buffList);)
    {
        temp = buffList[std::distance(buffList.begin(), i)];

        if (buff == buff)
        {
			i = buffList.erase(i);

			break;
		}
		else
			++i;
	}
	removeMods(buff->modList);
	//removeAbilities(buff->abilityList);
	removeTags(buff->tags);
	updateMods();
	generateChoiceDetailString();
	generateSlotDetailMap();
	return temp;
}

//Takes a list of mods to add and adds them to the this unit's modList.
int Unit::addMods(std::vector<std::shared_ptr<Mod>>& modList)
{
    for (auto mod : modList)
    {
        this->modList.push_back(mod);
    }
    return 0;
}

//Takes a list of mods to remove and removes them from the 
// this unit's modList.
int Unit::removeMods(std::vector<std::shared_ptr<Mod>>& modList)
{
    for (auto modToRemove : modList)
    {
        for (auto i = begin(this->modList); i != end(this->modList);)
        {
            if (modToRemove->owner == (*i)->owner)
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

//Goes throug the modList and updates the mod<STAT> variables
// such as modHitpoints, modAttack, and modDefense.
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
                modHitPoints += (int)std::ceil(mod->value);
            else if (mod->stat == Mod::ATTACK)
                modAttack += (int)std::ceil(mod->value);
            else if (mod->stat == Mod::DEFENSE)
                modDefense += (int)std::ceil(mod->value);
        }
    }

    float modHitPointsAddVal = float(modHitPoints);
    float modAttackAddVal = float(modAttack);
    float modDefenseAddVal = float(modDefense);
    float hpMultFactor = 1.;
    float atkMultFactor = 1.;
    float defMultFactor = 1.;

    for (auto mod : modList)
        if (mod->type == Mod::MULTIPLY)
        {
            if (mod->stat == Mod::HITPOINTS)
                hpMultFactor +=  mod->value;
            else if (mod->stat == Mod::ATTACK)
                atkMultFactor += mod->value;
            else if (mod->stat == Mod::DEFENSE)
                defMultFactor += mod->value;
        }

    modHitPoints = (int)std::ceil(modHitPointsAddVal * hpMultFactor);
    modAttack = (int)std::ceil(modAttackAddVal * atkMultFactor);
    modDefense = (int)std::ceil(modDefenseAddVal * defMultFactor);

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

// NOT FOR NORMAL USE, this is for making a blank unit for cereal
Unit::Unit()
    : GameObject(""),
    baseHitPoints(),
    baseAttack(),
    baseDefense(),
    modHitPoints(),
    modAttack(),
    modDefense(),
    type(),
    weapon(),
    armor(),
    trinket(),
    modList()
{}

//NOT FOR NORMAL USE, this is for saving a unit to the Unit.json file
void Unit::save()
{
    std::fstream file;
    file.open("resources/jsonArchives/Unit.json", std::ios::app);
    cereal::JSONOutputArchive archive(file);
    auto const objname = this->name;
    archive(cereal::make_nvp(objname, *this));
}