#pragma once
#include "GameObject.h"
#include "Mod.h"
#include "../sys/IAbilityDirector.h"


class Buff :
    public GameObject
{
public:
    //Basic attributes
    int durability;
    std::vector<std::shared_ptr<Mod>> modList;
    std::vector<std::shared_ptr<GameObject>> abilityList; // temp until Abilities are implemented

    //Constructors
    Buff( std::string name
        , int durability
        , std::vector<std::shared_ptr<Mod>> modList
        , std::vector<std::shared_ptr<GameObject>> abilityList
    );

    Buff(std::string key);

    //Basic methods


private:
    //For serialization
    std::vector<std::string> modKeyList;
    std::vector<std::string> abilityKeyList;
    std::vector<std::string> tagKeyList;
    Buff();
    void save();
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& ar)
    {
        modKeyList.clear();
        for (auto const x : modList)
	        modKeyList.push_back(x->name);
        abilityKeyList.clear();
        for (auto const x : abilityList)
	        abilityKeyList.push_back(x->name);
        tagKeyList.clear();
        for (auto const x : tags)
	        tagKeyList.push_back(x.first);
        
        ar(   CEREAL_NVP(durability)
            , CEREAL_NVP(modKeyList)
            , CEREAL_NVP(abilityKeyList)
            , CEREAL_NVP(tagKeyList)
        );

	}
};

