// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include "sys/Prompt.h"
#include "sys/PrntScrn.h"
#include "sys/Events.h"
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
#include "sys/IAbilityDirector.h"


void printBreak()
{
    std::cout << "\n~~~~~~~~~\n\n";
    return;
}

void eventTest01()
{
    //First create the event. This event here takes a reference to a string const.
    Events::event<const std::string&> printEvent;

    //Then create event handlers to add to it. The lambda takes an argument for a string const.
    Events::event_handler<const std::string&> printEventHandler1(
        [](const std::string& str) { std::cout << "printEventHandler1: " << str << std::endl; });

    //subscribe the event handler to the event
    std::cout << "Adding printEventHandler1 to printEvent.\n";
    printEvent.add(printEventHandler1);

    //call the event with a string const as an argument.This will call all of the event handlers
    // subscribed to the event and pass the string const to them.
    std::cout << "Calling printEvent. with 'Hello, world!' as argument\n";
    printEvent.call_async("Hello, world!");
    printBreak();

    //create another event handler that takes a string const as an argument, but 
    // won't print out "Hello, world!".
    Events::event_handler<const std::string&> printEventHandler2(
		[](const std::string& str) { 
            std::string myString = str;
            if (str == "Hello, world!")
				myString = "Goodbye, world!";
            std::cout << "printEventHandler2: " << myString << std::endl; });

    //subscribe the event handler to the event
    std::cout << "Adding printEventHandler2 to printEvent.\n";
    std::cout << "printEventHandler2 will change 'Hello, world!' to 'Goodbye, world!'\n";
    printEvent.add(printEventHandler2);


    // call the event with 'Hello, world!'
    std::cout << "Calling printEvent with 'Hello, world!' as argument\n";
    printEvent.call("Hello, world!");
    printBreak();

    // calling the event with 'Good Morning, world!'
    std::cout << "Calling printEvent with 'Good Morning, world!' as argument\n";
    printEvent.call("Good Morning, world!");
    printBreak();

    // remove the first event handler from the event
    std::cout << "Removing printEventHandler1 from printEvent.\n";
    printEvent.remove(printEventHandler1);

    // call the event with 'Hello, world!'
    std::cout << "Calling printEvent with 'Hello, world!' as argument\n";
    printEvent.call("Hello, world!");


    return;
}

void iabilityTest1()
{
    //You need to create the ability
    std::shared_ptr<Unit> myUnit = std::make_shared<Unit> ("TestUnit");
    std::shared_ptr<IAbility> myIAbility = IAbilityDirector::getIAbility("Decrement", myUnit);
    // add the ability to a buff
    // confirm the ability is in the buff
    // add the buff to the unit
    // confirm the iability is on the unit
    // confirm the iability event is registered on the currGS.
    // trigger the ability
    // remove the buff from the unit
    // confirm the iability is not on the unit
    // confirm the iability event is not registered on the currGS.


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
    //GM_Campaign newCampaign;

    //newCampaign.prepLoop();

    //newCampaign.preCombatLoop();

    //consumableTest();


    //newCampaign.preCombatLoop();

    //consumableTest();

    //statListTest();

    //itemListTest();

    //eventTest01();

    iabilityTest1();
}
