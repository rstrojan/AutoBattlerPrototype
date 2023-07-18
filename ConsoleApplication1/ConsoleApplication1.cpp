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
#include "gameObjectClasses/Buff.h"
#include "gameObjectClasses/Consumable.h"




void printBreak()
{
    std::cout << "\n~~~~~~~~~\n\n";
    return;

}

void consumableTest()
{
    Consumable myConsumable("TestConsumable");
    std::cout << myConsumable.name << std::endl;
}

void itemListTest()
{
    Unit myUnit("TestUnit");
    std::cout << "Unit base attack: " << myUnit.getStat("BASE_ATTACK") << std::endl;
    std::cout << "Unit mod attack: " << myUnit.getStat("MOD_ATTACK") << std::endl;
    std::cout << "Adding Item with +1 attack.\n";
    std::shared_ptr<Item> myItem = std::make_shared<Item>("Sword");
    myUnit.addItem(myItem);
    std::cout << "Weapon added.\n";
    std::cout << "Unit mod attack: " << myUnit.getStat("MOD_ATTACK") << std::endl;
    std::cout << "Removing Item with +1 attack.\n";
    myUnit.removeItem("WEAPON");
    std::cout << "Unit mod attack: " << myUnit.getStat("MOD_ATTACK") << std::endl;
}

void statListTest()
{
    Unit myUnit("TestUnit");
    std::cout << "Unit base attack: " << myUnit.getStat("BASE_ATTACK") << std::endl;
    std::cout << "Unit mod attack: " << myUnit.getStat("MOD_ATTACK") << std::endl;
    std::cout << "Adding buff with +1 attack.\n";
    std::shared_ptr<Buff> myBuff = std::make_shared<Buff>("TestBuff");
    myUnit.addBuff(myBuff);
    std::cout << "Buff added.\n";
    std::cout << "Unit mod attack: " << myUnit.getStat("MOD_ATTACK") << std::endl;
    std::cout << "Removing Item with +1 attack.\n";
    myUnit.removeBuff(myBuff);
    std::cout << "Buff removed.\n";
    std::cout << "Unit mod attack: " << myUnit.getStat("MOD_ATTACK") << std::endl;

}


int main()
{
    GM_Campaign newCampaign;

    newCampaign.prepLoop();

    newCampaign.preCombatLoop();

    //consumableTest();

    //statListTest();

    //itemListTest();
}
