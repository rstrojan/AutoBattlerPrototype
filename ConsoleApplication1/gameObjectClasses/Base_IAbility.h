#pragma once
#include <chrono>
#include <memory>
#include "GameObject.h"
#include "Unit.h"
#include "../sys/Events.h"
#include "../modeAndStateClasses/GS_Campaign.h"


class Base_IAbility :
    public GameObject
{
public:
    //Basic attributes
    std::string desc;
    std::shared_ptr<GameObject> owner;
    bool isHidden;

    //Constructors
    Base_IAbility(std::string name
        , std::string desc
        , bool isHidden
        , std::shared_ptr<GameObject> owner
    );
    Base_IAbility(std::string key, std::shared_ptr<GameObject> owner);

    //Basic Methods
    //static std::shared_ptr<Base_Ability> getAbility(std::string key, std::shared_ptr<GameObject> owner);

private:
    //For serialization
    std::vector<std::string> tagKeyList;
    Base_IAbility();
    void save();
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(CEREAL_NVP(desc)
            , CEREAL_NVP(isHidden)
            , CEREAL_NVP(tagKeyList)
        );
    }
};