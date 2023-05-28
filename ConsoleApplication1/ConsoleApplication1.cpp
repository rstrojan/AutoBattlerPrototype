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


void printBreak()
{
    std::cout << "\n~~~~~~~~~\n\n";
    return;

}


int main()
{
    //GM_Campaign newCampaign;

    //newCampaign.prepLoop();

    //newCampaign.preCombatLoop();

    Item myItem("Sword");
    std::cout << "Number of Weapon tags: " << myItem.tagCount("Weapon") << "\n";
    Unit myUnit("Ryan1");
    myUnit.addItem(std::make_shared<Item>(myItem));
    myUnit.removeItem(Item::WEAPON);
    Unit my2ndUnit("Ryan2");
    Unit my3rdUnit("Ryan1");
}
