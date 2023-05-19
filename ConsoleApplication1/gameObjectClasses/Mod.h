#pragma once
#include "GameObject.h"
class Mod :
    public GameObject
{
public:
    enum statType : std::uint8_t { HITPOINTS, ATTACK, DEFENSE };
    enum modType : std::uint8_t { ADD, MULTIPLY };
    statType stat;
    modType type;
    float value;
    std::shared_ptr<GameObject> owner;
    Mod(std::string name, statType stat, modType type, float value, std::shared_ptr<GameObject> owner);
    Mod(std::string key, std::shared_ptr<GameObject> owner);

    void save();

private:
    Mod();
    friend class cereal::access;

    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(CEREAL_NVP(stat),
            CEREAL_NVP(type),
            CEREAL_NVP(value));
    }
};

