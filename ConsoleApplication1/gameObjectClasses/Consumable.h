#pragma once
#include "GameObject.h"
#include "Buff.h"
#include "RuleSet.h"

class Buff;

class Consumable :
    public GameObject
{
public:
    enum consumableType : std::uint8_t { POTION, FOOD, SCROLL, BOOK, OTHER };


    //Basic attributes
    consumableType type;
    std::vector<std::shared_ptr<Buff>> buffList;
    std::shared_ptr<RuleSet> ruleSet;

    //Constructors
    Consumable(
          std::string name
        , consumableType type
        , std::vector<std::shared_ptr<Buff>> buffList
    );
    Consumable(std::string key);

    //Basic methods

private:
    //For serialization
    std::string ruleSetKey;
    std::vector<std::string> buffKeyList;
    std::vector<std::string> tagKeyList;
    Consumable();
    void save();
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& ar)
    {
        if (ruleSet != NULL)
            ruleSetKey = ruleSet->name;
        buffKeyList.clear();
        for (auto const x : buffList)
            buffKeyList.push_back(x->name);
        tagKeyList.clear();
        for (auto const x : tags)
            tagKeyList.push_back(x.first);
        
        ar(   CEREAL_NVP(type)
            , CEREAL_NVP(ruleSetKey)
            , CEREAL_NVP(buffKeyList)
            , CEREAL_NVP(tagKeyList)
        );
    }

};

