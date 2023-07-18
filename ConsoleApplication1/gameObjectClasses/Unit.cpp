#include "Unit.h"

Unit::Unit(std::string name
    , std::string type
    , std::vector<std::shared_ptr <Mod>> modList
    , std::vector<std::shared_ptr <Buff>> buffList
)
    : GameObject(name)
    , type(type)
    , modList(modList)
    , buffList(buffList)
    , statMap({
            {"baseAttack",     1}
           ,{"baseDefense",    0}
           ,{"baseHitPoints", 10}
           ,{"level",          1}
           })
    , itemMap()
{
    updateMods();
    generateChoiceDetailString();
    generateSlotDetailMap();
}

//Takes a key and loads the unit from the Unit.json file
Unit::Unit(std::string key)
    : GameObject(key)
    , type()
    , modList()
    , buffList()
    , statMap()
    , itemMap()
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
    //itemMap works a little differently than some of the other lists and maps
    //that need keys when loading from json. The itemMap's first value is the TYPE
    //of item, not the name of the item. However, we store the name of the item
    // in the json so that the constructor will work. So we need to add another step here
    // for this one so that we store the type/itemptr pair in the map.
    for (auto const& x : unitData.itemKeyList)
    {
        std::shared_ptr<Item> tempItem = std::make_shared<Item>(x);
        itemMap.emplace(std::make_pair(tempItem->type, tempItem));
    }


    this->type    = unitData.type;
    this->statMap = unitData.statMap;
    this->itemMap = unitData.itemMap;


    updateMods();
}

//Adds an item to one of the three item slots
// depending on the item's type.
void Unit::addItem(std::shared_ptr<Item> item)
{
    itemMap.emplace(std::make_pair(item->type, item));

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
std::shared_ptr <Item> Unit::removeItem(std::string type)
{
    std::shared_ptr <Item> temp;
    auto it = itemMap.find(type);
    if (it != itemMap.end())
    {
		temp = it->second;
		itemMap.erase(it);
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



//Takes a string and uses it to find a stat in the unit's statMap.
// Returns the value of the stat if found, otherwise returns NULL.
float Unit::getStat(std::string stat)
{
    auto it = statMap.find(stat);
    if (it != statMap.end())
        return it->second;
    else
        return NULL;
}

//Takes a string and tries to match it to an Item in the unit's itemMap.
// Returns a pointer to the item if found, otherwise returns NULL.
std::shared_ptr <Item> Unit::getItem(std::string type)
{
	auto it = itemMap.find(type);
	if (it != itemMap.end())
		return it->second;
	else
		return NULL;
}

//Removes a buff from the unit's buffList as well as the
// mods, abilities, and tags of the buff.
std::shared_ptr <Buff> Unit::removeBuff(std::shared_ptr<Buff> buff)
{
    std::shared_ptr<Buff> temp;
    for (auto i = begin(buffList); i != end(buffList);)
    {
        temp = buffList[std::distance(buffList.begin(), i)];

        if (temp == buff)
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
    //statmap mod reset blcok
    statMap["MOD_HITPOINTS"] = statMap["BASE_HITPOINTS"];
    statMap["MOD_ATTACK"] = statMap["BASE_ATTACK"];
    statMap["MOD_DEFENSE"] = statMap["BASE_DEFENSE"];

    //statmap add block
    for (auto mod : modList)
    {
        if (mod->type == "ADD")
        {
            statMap[mod->stat] += (int)std::ceil(mod->value);
        }
    }

    return 0;
}

//Creates or updates a string of key details of the 
// object for use as a choice in a Prompt.
void Unit::generateChoiceDetailString()
{
    updateMods();
    choiceDetailString = 
          name 
        + "(" + type + ")"
        + "|H:" + std::to_string((int)std::ceil(getStat("MOD_HITPOINTS")))
        + "|A:" + std::to_string((int)std::ceil(getStat("MOD_ATTACK")))
        + "|D:" + std::to_string((int)std::ceil(getStat("MOD_DEFENSE")));
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
    slotDetailMap["L3"] = "H:" + std::to_string((int)std::ceil(getStat("MOD_HITPOINTS")))
                        + "|A:" + std::to_string((int)std::ceil(getStat("MOD_ATTACK")))
                        + "|D:" + std::to_string((int)std::ceil(getStat("MOD_DEFENSE")));
    slotDetailMap["L4"] = "Mods:";
    std::string lineIndexString;
    int lineIndex = 4;
    for (auto mod : modList)
    {
        lineIndex++;
        lineIndexString = "L" + std::to_string(lineIndex);
		slotDetailMap[lineIndexString] = mod->name;
	}
    return;
}

// NOT FOR NORMAL USE, this is for making a blank unit for cereal
Unit::Unit()
    : GameObject("")
    , type()
    , modList()
    , buffList()
    , statMap()
    , itemMap()
{}

//NOT FOR NORMAL USE, this is for saving a unit to the Unit.json file
void Unit::save()
{
    std::fstream file;
    file.open("resources/jsonArchives/test.json", std::ios::app);
    cereal::JSONOutputArchive archive(file);
    auto const objname = this->name;
    archive(cereal::make_nvp(objname, *this));
}