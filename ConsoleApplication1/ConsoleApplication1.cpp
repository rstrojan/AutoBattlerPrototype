// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "sys/Prompt.h"
#include "sys/PrntScrn.h"
#include "modeAndStateClasses/GM_Campaign.h"
#include "gameObjectClasses/GameObject.h"
#include "gameObjectClasses/Mod.h"
#include "gameObjectClasses/Item.h"
#include "gameObjectClasses/Player.h"
#include "gameObjectClasses/Unit.h"
#include "gameObjectClasses/Rule.h"
#include "gameObjectClasses/RuleSet.h"



void printBreak()
{
    std::cout << "\n~~~~~~~~~\n\n";
    return;

}


int main()
{
    GM_Campaign newCampaign;

    //newCampaign.prepLoop();

    //newCampaign.preCombatLoop();

    Item myItem("Sword");
    RuleSet myRuleSet("WeaponCheck");
    Rule myRule("Weapon>0");

    std::cout << "MultiTagCheck: " << newCampaign.multiTagCheck(myItem, myRuleSet) << "\n";
    std::cout << "TagCheck: " << newCampaign.tagCheck(myItem, myRule) << "\n";


}
