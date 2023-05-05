#pragma once
#include <map>
#include <vector>
#include <string>
#include "Mod.h"
#include "GameObject.h"
class Item :
    public GameObject
{
public:
    enum itemType { WEAPON, ARMOR, TRINKET };
    Item(std::string name, itemType type, int durability, int hitPointModifier, int attackModifier, int defenseModifier,
        std::vector<std::string> modKeys);
    itemType type;
    int hitPointModifier;
    int attackModifier;
    int defenseModifier;
    int durability;
    std::vector<Mod> modList;
    
};

