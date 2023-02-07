// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Prompt.h"
#include "PrntScrn.h"


void printBreak()
{
    std::cout << "\n~~~~~~~~~\n\n";
    return;

}

void mockUp()
{
    Prompt userPrompt;
    PrntScrn ps;

    //EVENTUALLY YOU NEED TO BREAK EACH OF THE CAMPAIGN LOOPS INTO 
    //THEIR OWN FUNCTIONS, ONCE ACTUALLY START ADDING LOGIC TO THIS STUFF.
    //THAT WAY IN MAIN YOU'RE JUST CALLING A SERIES OF FUNCTIONS INSTEAD OF 
    //ALL OF THE PIDDLY DETAILED STUFF.

    //START MENU
    //Player must choose start new or load game.

  

    std::cout << "***************\n"
        << "Welcome to my game mock up. First up we're coming to the \n"
        << "Campaign Prep Loop, which is where the player chooses what \n"
        << "they're going to bring with them on their battles.\n"
        << "Ideally, players will bring along a few of each of the\n"
        << "supplies. They can't take everything, and that's ok because\n"
        << "they will get loot out on the battle fields.\n\n";
    userPrompt.ask("STARTMENU", "1");
    printBreak();


    //prep for displaying the screen:
    std::map<std::string, std::string> reinforcements = { {"title","Reinforcements"} };
    std::map<std::string, std::string> vanguard = { {"title","Vanguard"},{"Field Mice","5"} };
    std::map<std::string, std::string> equipment = { {"title","Equipment"},{"Spear","5"},{"Sword","3"} }; 
    std::map<std::string, std::string> consumables = { {"title","Consumable"} };
    std::map<std::string, std::string> tempMap = { {"title","Inventory"}, {"Spears","0"}};
    ps.assignSlot(1, equipment);
    ps.assignSlot(2, vanguard);
    ps.assignSlot(3, consumables);
    ps.assignSlot(4, reinforcements);
    ps.assignSlot(5,tempMap);



    //First let's have them choose some equipment
    ps.clearAndPrint("*****First, choose equipment.\n\n");
    while (userPrompt.ask("CAMPAIGNPREPLOOP", "1") != "1") {}
    std::cout << "\nYou choose to add some equipment!\n";

    //Try adding some spears.
    ps.clearAndPrint("\n*****Choose spears.\n\n");
    while (userPrompt.ask("CHOOSEEQUIPMENT", "2") != "2") {}
    std::cout << "\nYou choose to add some spears.\n";

    //Add 5
    ps.clearAndPrint("\n*****Add some!\n\n");
    userPrompt.ask("HOWMANY", "\\d+");
    tempMap["Spears"] = userPrompt.getInput();
    std::cout << "\nYou added " + userPrompt.getInput() + " spears.\n";

    //Let's choose consumables.
    ps.clearAndPrint("*****Choose your consumables.\n\n");
    while (userPrompt.ask("CAMPAIGNPREPLOOP", "2") != "2") {}
    std::cout << "\nYou choose to add some consumables.\n";

    //Choose the hearty meal!
    ps.clearAndPrint("\n*****Choose a hearty meal!.\n\n");
    while (userPrompt.ask("CHOOSECONSUMABLE", "1") != "1");
    std::cout << "\nYou choose to add some Hearty Meals.\n";

    //Add 5
    ps.clearAndPrint("\n*****Add some!\n\n");
    userPrompt.ask("HOWMANY", "\\d+");
    std::cout << "\nYou added " + userPrompt.getInput() + " Hearty Meals.\n";

    //Choose your Vanguard
    ps.clearAndPrint("\n*****Choose your vanguard.\n\n");
    while (userPrompt.ask("CAMPAIGNPREPLOOP", "3") != "3") {}
    std::cout << "\nYou choose to add to your vanguard.\n";

    //Let's make a team of field mice.
    std::cout << "\n*****Let's add field mice.\n\n";
    while (userPrompt.ask("SETVANGUARD", "1") != "1") {}
    std::cout << "\nYou choose to add some field mice.\n";

    //Add 5
    std::cout << "\n*****Pick 5, which is a full squad!\n\n";
    userPrompt.ask("HOWMANY", "\\d+");
    std::cout << "\nYou added " + userPrompt.getInput() + " field mice.\n";

    //Choose your reinforcements
    std::cout << "\n*****Choose your reinforcements.\n\n";
    while (userPrompt.ask("CAMPAIGNPREPLOOP", "4") != "4") {}
    std::cout << "\nYou choose to add to your reinforcements.\n";

    //Choose your reinforcements
    std::cout << "\n******Choose your reinforcements.\n\n";
    while (userPrompt.ask("SETREINFORCEMENTS", "2") != "2") {}
    std::cout << "\nYou choose to add some song birds.\n";

    //Add 5
    std::cout << "\n*****Pick some!\n\n";
    userPrompt.ask("HOWMANY", "\\d+");
    std::cout << "\nYou added " + userPrompt.getInput() + " song birds to your reinforcements.\n";

    //That's all.
    std::cout << "\nThat's all of the Campaign Prep Loop options.\n"
        << "Choose Start Campaign!\n\n";
    while (userPrompt.ask("CAMPAIGNPREPLOOP", "5") != "5") {}
    std::cout << "You choose to start the campaign. Good luck!\n";

    std::cout << "\n\nAnd that's it for now!!\n\n";

    return;
}

int main()
{

    mockUp();
    //PrntScrn ps;
    //ps.clearAndPrint("Hello");

    //Prompt prompt1;
    
    ////basic open text response prompt
    //std::cout << "Test 01: Basic written response prompt.\n";
    //prompt1.ask("Q1");
    //std::cout << "User input: " << prompt1.getInput() << '\n';
    //printBreak();
    //
    ////basic multi choice response prompt
    //std::cout << "Test 02: Basic multi response prompt.\n";
    //prompt1.ask("Q2");
    //std::cout << "User input: " << prompt1.getInput() << '\n';
    //printBreak();
    //
    ////open text response prompt with all caps validation override
    //std::cout << "Test 03: Written response prompt with all caps validation override.\n";
    //prompt1.ask("Q1", "[A-Z]+");
    //std::cout << "User input: " << prompt1.getInput() << '\n';
    //printBreak();

    ////multi choice resposne with choices override
    //std::cout << "Test 04: Multi choice response with choices override.\n";
    ////You can skip the optional validationOverride by entering in "NULL"
    //prompt1.ask("Q2","NULL", {"Pick this one.", "Not this one, thank you."});
    //std::cout << "User input: " << prompt1.getInput() << '\n';
    //printBreak();

    ////basic open text response prompt with multi choice override
    //std::cout << "Test 05: Basic written respone with choice override.\n";
    //prompt1.ask("Q1", "NULL", { "You shouldn't see this.", "Or this!" });
    //std::cout << "User input: " << prompt1.getInput() << '\n';
    //printBreak();

    ////Multi choice response with validation override
    //std::cout << "Test 06: Multi choice response with validation override.\n";
    //prompt1.ask("Q2", "\\d{1}");
    //std::cout << "User input: " << prompt1.getInput() << '\n';
    //printBreak();

    //std::cout << "End of tests.\n\n";

}
