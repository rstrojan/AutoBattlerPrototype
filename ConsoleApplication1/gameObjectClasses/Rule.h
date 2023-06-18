#pragma once
#include "GameObject.h"
class Rule :
    public GameObject
{
public:
    //Basic attributes
    int count;
    std::string targetTag;
    std::string ruleOp;
    
    //constructors
    Rule(std::string name, std::string targetTag, std::string ruleOp, int count);
    Rule(std::string key);

    //basic methods

private:
    //for serialization
	Rule();
	void save();
	friend class cereal::access;
	template <class Archive>
    void serialize(Archive& ar)
    {
		ar(CEREAL_NVP(count),
			CEREAL_NVP(targetTag),
			CEREAL_NVP(ruleOp));
	}
};

