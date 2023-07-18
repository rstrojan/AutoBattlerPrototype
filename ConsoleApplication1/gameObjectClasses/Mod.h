#pragma once
#include "GameObject.h"
class Mod :
    public GameObject
{
public:
    //Basic attributes
    std::string stat;
    std::string type;
    float value;
    std::shared_ptr<GameObject> owner;

    //Constructors
    Mod(  std::string name
        , std::string stat
        , std::string type
        , float value
        , std::shared_ptr<GameObject> owner
    );
    Mod(std::string key, std::shared_ptr<GameObject> owner);

    //Basic methods

private:

    //For serialization
    Mod();
    void save();
    friend class cereal::access;

    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(   CEREAL_NVP(stat)
            , CEREAL_NVP(type)
            , CEREAL_NVP(value)
        );
    }
};

