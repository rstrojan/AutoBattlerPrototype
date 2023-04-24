#pragma once
#include "GameObject.h"
class Item :
    public GameObject
{
public:
    enum itemType { WEAPON, ARMOR, TRINKET };
    Item(std::string name, itemType type, int durability, int hitPointModifier, int attackModifier, int defenseModifier);
    itemType type;
    int hitPointModifier;
    int attackModifier;
    int defenseModifier;
    int durability;

    
};

