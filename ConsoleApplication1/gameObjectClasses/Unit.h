#pragma once
#include "GameObject.h"
#include "Item.h"
#include "Mod.h"
class Unit :
    public GameObject
{
public:
    //Basic attributes
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

    //Constructors
    Unit(std::string name, std::string type, int baseHitPoints, int baseAttack, int baseDefense);
    Unit(std::string key);

    //Basic methods
    void addItem(std::shared_ptr <Item> item);
    std::shared_ptr <Item> removeItem(Item::itemType type);


private:
    int addMods(std::vector<Mod> &modList);
    int removeMods(std::vector<Mod>& modList);
    int updateMods();
    
    // For serialization
    std::vector<std::string> modKeyList;
    std::string weaponKey;
    std::string armorKey;
    std::string trinketKey;
    Unit();
    void save();
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& ar)
    {
        if(weapon != NULL)
            weaponKey = weapon->name;;
        if(armor != NULL)
            armorKey = armor->name;
        if(trinket != NULL)
            trinketKey = trinket->name;
        modKeyList.clear();
        for (auto const x : modList)
            modKeyList.push_back(x->name);
        ar(CEREAL_NVP(type),
        CEREAL_NVP(baseHitPoints),
        CEREAL_NVP(baseAttack),
        CEREAL_NVP(baseDefense),
        CEREAL_NVP(weaponKey),
        CEREAL_NVP(armorKey),
        CEREAL_NVP(trinketKey),
        CEREAL_NVP(modKeyList)
        );
    }
protected:
    void generateChoiceDetailString();
    void generateSlotDetailMap();
};

