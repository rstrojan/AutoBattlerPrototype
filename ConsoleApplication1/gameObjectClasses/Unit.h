#pragma once
#include "GameObject.h"
#include "Item.h"
#include "Mod.h"
#include "Buff.h"

class Buff;
class Unit :
    public GameObject
{
public:
    //Basic attributes
    std::string type;
    std::vector<std::shared_ptr <Mod>> modList;
    std::vector<std::shared_ptr <Buff>> buffList;
    

    //Constructors
    Unit( std::string name
        , std::string type
        , std::vector<std::shared_ptr <Mod>> modList
        , std::vector<std::shared_ptr <Buff>> buffList
    );
    Unit(std::string key);

    //Basic methods
    void addItem(std::shared_ptr <Item> item);
    std::shared_ptr <Item> removeItem(std::string type);
    void addBuff(std::shared_ptr <Buff> buff);
    std::shared_ptr <Buff> removeBuff(std::shared_ptr<Buff> buff);
    float getStat(std::string stat);
    std::shared_ptr <Item> getItem(std::string type);


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
    Unit();
    void save();
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& ar)
    {
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

        ar(CEREAL_NVP(type)
            , CEREAL_NVP(modKeyList)
            , CEREAL_NVP(tagKeyList)
            , CEREAL_NVP(buffKeyList)
            , CEREAL_NVP(statMap)
            , CEREAL_NVP(itemKeyList)
        );
    }
protected:
    void generateChoiceDetailString();
    void generateSlotDetailMap();
};