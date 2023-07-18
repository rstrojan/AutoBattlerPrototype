#pragma once

#include "Mod.h"
#include "GameObject.h"
class Item :
    public GameObject
{
public:
    //Basic attributes
    std::string type;
    int durability;
    std::vector<std::shared_ptr<Mod>> modList;
    
    //Constructors
    Item( 
          std::string name
        , std::string type
        , int durability
        , std::vector<std::shared_ptr<Mod>> modList
    );
    Item(std::string key);

    //basic methods



private:

    //For serialization
    friend class cereal::access;
    Item();
    void save();
    std::vector<std::string> modKeyList; //holds keys for mods
    std::vector<std::string> tagKeyList; //holds keys for tags
    template <class Archive>
    void serialize(Archive& ar)
    {
        modKeyList.clear();
        for (auto const x : modList)
        {
            modKeyList.push_back(x->name);
        }
        tagKeyList.clear();
        for (auto const x : tags)
        {
            tagKeyList.push_back(x.first);
        }

        ar(   CEREAL_NVP(type)
            , CEREAL_NVP(durability)
            , CEREAL_NVP(modKeyList)
            , CEREAL_NVP(tagKeyList)
        );
    }

protected:
    void generateChoiceDetailString();
};

