#pragma once
#include "GameObject.h"
class Unit :
    public GameObject
{
public:
    Unit(std::string name, std::string type, int hitPoints, int attack, int defense);
    int hitPoints;
    int attack;
    int defense;
    std::string type;
    std::shared_ptr <GameObject> weapon;
    std::shared_ptr <GameObject> armor;
    std::shared_ptr <GameObject> trinket;


protected:
    void generateChoiceDetailString();
    void generateSlotDetailMap();
};

