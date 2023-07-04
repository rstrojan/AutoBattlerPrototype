#pragma once
#include "GameObject.h"
#include "Item.h"
#include "Mod.h"
#include "Buff.h"
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
    std::vector<std::shared_ptr <Buff>> buffList;
    

    //Constructors
    Unit(std::string name, std::string type, int baseHitPoints, int baseAttack, int baseDefense);
    Unit(std::string key);

    //Basic methods
    void addItem(std::shared_ptr <Item> item);
    std::shared_ptr <Item> removeItem(std::string type);
    void addBuff(std::shared_ptr <Buff> buff);
    std::shared_ptr <Buff> removeBuff(std::shared_ptr<Buff> buff);
    float getStat(std::string stat);


private:
    std::map<std::string, float> statMap;
    std::map<std::string, std::shared_ptr<Item>> itemMap;
    int addMods(std::vector<std::shared_ptr<Mod>>&modList);
    int removeMods(std::vector<std::shared_ptr<Mod>>& modList);
    int updateMods();
    
    // For serialization
    std::vector<std::string> modKeyList;
    std::vector<std::string> tagKeyList;
    std::vector<std::string> buffKeyList;
    std::vector<std::string> itemKeyList;
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
        tagKeyList.clear();
        for (auto const x: tags)
            tagKeyList.push_back(x.first);
        buffKeyList.clear();
        for (auto const x : buffList)
            buffKeyList.push_back(x->name);
        itemKeyList.clear();
        for (auto const x : itemMap)
            itemKeyList.push_back(x.second->name);
        ar(CEREAL_NVP(type),
        CEREAL_NVP(baseHitPoints),
        CEREAL_NVP(baseAttack),
        CEREAL_NVP(baseDefense),
        CEREAL_NVP(weaponKey),
        CEREAL_NVP(armorKey),
        CEREAL_NVP(trinketKey),
        CEREAL_NVP(modKeyList),
        CEREAL_NVP(tagKeyList),
        CEREAL_NVP(buffKeyList),
        CEREAL_NVP(statMap),
        CEREAL_NVP(itemKeyList)
        );
    }
protected:
    void generateChoiceDetailString();
    void generateSlotDetailMap();
};