#pragma once
#include "GameObject.h"
#include "Item.h"
class Unit :
    public GameObject
{
public:
    Unit(std::string name, std::string type, int hitPoints, int attack, int defense);
    int hitPoints;
    int attack;
    int defense;
    std::string type;
    std::shared_ptr <Item> weapon;
    std::shared_ptr <Item> armor;
    std::shared_ptr <Item> trinket;

    void addItem(std::shared_ptr <Item> item);
    std::shared_ptr <Item> removeItem(Item::itemType type);

protected:
    void generateChoiceDetailString();
    void generateSlotDetailMap();
};

