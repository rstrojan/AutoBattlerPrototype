#pragma once
#include "GameObject.h"
class Mod :
    public GameObject
{
public:
    enum statType { HITPOINTS, ATTACK, DEFENSE };
    enum modType { ADD, MULTIPLY };
    statType stat;
    modType type;
    float value;
    std::shared_ptr<GameObject> owner;

    Mod(std::string name, statType stat, modType type, float value, std::shared_ptr<GameObject> owner);
};

