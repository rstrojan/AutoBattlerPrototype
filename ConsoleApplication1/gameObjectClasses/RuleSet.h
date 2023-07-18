#pragma once
#include "GameObject.h"
#include "Rule.h"

class RuleSet :
    public GameObject
{
public:
    //Basic attributes
    std::string logOp;
    std::vector<std::shared_ptr<Rule>> ruleList;

    //Constructors
    RuleSet(
          std::string name
        , std::string logOp
        , std::vector<std::shared_ptr<Rule>> ruleList
    );
    RuleSet(std::string key);


    //Basic methods

private:
    //For serialization
    std::vector<std::string> ruleKeyList;
    RuleSet();
    void save();
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& ar)
    {
        ruleKeyList.clear();
        for (auto const x : ruleList)
            ruleKeyList.push_back(x->name);
        
        ar(   CEREAL_NVP(logOp)
            , CEREAL_NVP(ruleKeyList)
        );
    }
};