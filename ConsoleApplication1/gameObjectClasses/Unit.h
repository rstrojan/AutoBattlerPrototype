#pragma once
#include <vector>
#include "GameObject.h"
#include "Item.h"
#include "Mod.h"
class Unit :
    public GameObject
{
public:
    Unit(std::string name, std::string type, int baseHitPoints, int baseAttack, int baseDefense);
    int baseHitPoints;
    int baseAttack;
    int baseDefense;
    int modHitPoints;
    int modAttack;
    int modDefense;
    std::string type;
    std::shared_ptr <Item> weapon;
    std::shared_ptr <Item> armor;
    std::shared_ptr <Item> trinket;
    std::vector<std::shared_ptr <Mod>> modList;

    void addItem(std::shared_ptr <Item> item);
    std::shared_ptr <Item> removeItem(Item::itemType type);

private:
    int addMods(std::vector<Mod> &modList);
    int removeMods(std::vector<Mod>& modList);
    int updateMods();

protected:
    void generateChoiceDetailString();
    void generateSlotDetailMap();
};

