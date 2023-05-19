#pragma once

#include "Mod.h"
#include "GameObject.h"
class Item :
    public GameObject
{
public:
    enum itemType : std::uint8_t { WEAPON, ARMOR, TRINKET };
    Item(std::string name, itemType type, int durability, int hitPointModifier, int attackModifier, int defenseModifier, std::vector<Mod> modList);
    Item(std::string key);
    void save();
    itemType type;
    int hitPointModifier;
    int attackModifier;
    int defenseModifier;
    int durability;
    std::vector<Mod> modList;

private:
    Item();
    friend class cereal::access;
    std::vector<std::string> modKeyList;
    template <class Archive>
    void serialize(Archive& ar)
    {
        modKeyList.clear();
        for (auto const x : modList)
        {
            modKeyList.push_back(x.name);
        }

        ar(CEREAL_NVP(type),
        CEREAL_NVP(hitPointModifier),
        CEREAL_NVP(attackModifier),
        CEREAL_NVP(defenseModifier),
        CEREAL_NVP(durability),
        CEREAL_NVP(modKeyList));
	}
};

