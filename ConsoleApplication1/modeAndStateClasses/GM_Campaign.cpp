#include "GM_Campaign.h"

GM_Campaign::GM_Campaign() {};

//DEPRECATED - Please use chooseFromQuantityInv or chooseFromDetailInv
void GM_Campaign::chooseFromInv(std::string promptKey, std::map <std::string, std::string> &fromInv, std::map <std::string, std::string> &toInv)
{
    Prompt tempPrompt;
    PrntScrn tempScrn;
    tempScrn.assignSlot(1, fromInv);
    tempScrn.assignSlot(3, toInv);

    //first have the player pick the item
    std::vector<std::string> fromInvChoices;
    for (auto const& x : fromInv)
    {
        if (x.first != "title")
            fromInvChoices.push_back(x.first);
    }

    do { tempPrompt.ask(promptKey, "\\d+", fromInvChoices); } 
    while (stoi(tempPrompt.getInput()) <= 0 || stoi(tempPrompt.getInput()) > fromInvChoices.size());
    std::string selectionKey = fromInvChoices[stoi(tempPrompt.getInput()) - 1];

    //then have them pick the quantity
    do { tempPrompt.ask("HOWMANY", "\\d+"); }
    while (0 > ( stoi( fromInv[selectionKey] ) - stoi( tempPrompt.getInput() ) ) );
    auto item = toInv.find(selectionKey);

    if (item == toInv.end())
    {
        toInv[selectionKey] = tempPrompt.getInput();
    }
    else
    {
        int initialVal = stoi(toInv[selectionKey]);
        int newVal = stoi(tempPrompt.getInput()) + initialVal;
        toInv[selectionKey] = std::to_string(newVal);
    }

    int initialVal = stoi(fromInv[selectionKey]);
    int newVal = initialVal - stoi(tempPrompt.getInput());

    fromInv[selectionKey] = std::to_string(newVal);


	return;
}

//Prompts via a promptKey lookup and provides a list of choices from the fromInv,
//then allows user to set how much of their selection to be transferred to the 
//toInv.
void GM_Campaign::chooseFromQuantityInv(std::string promptKey, Inventory& fromInv, Inventory& toInv)
{
    Prompt tempPrompt;
    PrntScrn tempScrn;
    tempScrn.assignSlot(1, fromInv.quantityMap);
    tempScrn.assignSlot(3, toInv.quantityMap);
    tempScrn.clearAndPrint("");
    std::vector<std::string> fromInvChoices = fromInv.getQuantityChoiceVector();

    //first have the player pick the item and store the selection
    std::string selection =  tempPrompt.ask(promptKey, "NULL", fromInvChoices);

    //pick the quantity and validate
    do { tempPrompt.ask("HOWMANY", "\\d+"); } 
    while (0 > (stoi(fromInv.quantityMap[selection]) - stoi(tempPrompt.getInput())));
    
    //call transfer a number of times equal to the entered quantity
    for (int i = 0; i < std::stoi(tempPrompt.getInput()); i++)
        Inventory::transferItem(selection, fromInv, toInv);

    return;
}

//Prompts via a promptKey lookup and provies a list of choices from the fromInv,
//The choices give extra details based on the game objects choiceDetailString.
//Detailed view of the toInv is displayed in the slots.
void GM_Campaign::chooseFromDetailInv(std::string promptKey, Inventory& fromInv, Inventory& toInv)
{
    Prompt tempPrompt;
    PrntScrn tempScrn;

    tempScrn.assignSlots(toInv.getSlotDetailMaps());
    tempScrn.clearAndPrint("");
    std::vector<std::string> fromInvChoices = fromInv.getDetailedChoiceVector();

    //first have the player pick the item and store the selection
    std::string selection = tempPrompt.ask(promptKey, "NULL", fromInvChoices);

    //call transfer
    Inventory::transferItem(selection, fromInv, toInv);

    return;
}

//DEPRECATED
void GM_Campaign::chooseUnit(std::vector<std::string> fromInv, std::vector<std::string> toInv)
{
	return;
}

//This is temporarily overloaded with functionality that will be removed.
//The welcome prompt and instantiations will be removed.
void GM_Campaign::prepLoop()
{
    Prompt userPrompt;
    PrntScrn ps;
    std::cout << "***************\n"
        << "Welcome to my game mock up. First up we're coming to the \n"
        << "Campaign Prep Loop, which is where the player chooses what \n"
        << "they're going to bring with them on their battles.\n"
        << "Ideally, players will bring along a few of each of the\n"
        << "supplies. They can't take everything, and that's ok because\n"
        << "they will get loot out on the battle fields.\n\n";

    //Player must choose start new game.
        userPrompt.ask("STARTMENU", "New Game");
    

        //prep for displaying the screen:
        Player p("Player One");

        Inventory equipmentInv("Equipment");
        GameObject sword("Sword");
        GameObject spear("Spear");
        GameObject shield("Shield");
        equipmentInv.addItem(&sword, 8);
        equipmentInv.addItem(&spear, 8);
        equipmentInv.addItem(&shield, 8);

        Inventory consumableInv("Consumables");
        GameObject heartyMeal("Hearty Meal");
        GameObject quickSnack("Quick Snack");
        consumableInv.addItem(&heartyMeal, 20);
        consumableInv.addItem(&quickSnack, 20);

        Inventory unitInv("Units");
        GameObject mouse01("James");
        GameObject mouse02("Ryan");
        GameObject mouse03("Thom");
        GameObject mouse04("Doug");
        unitInv.addItem(&mouse01);
        unitInv.addItem(&mouse02);
        unitInv.addItem(&mouse03);
        unitInv.addItem(&mouse04);

        ps.assignSlot(1, p.equipmentInv.quantityMap);
        ps.assignSlot(2, p.consumableInv.quantityMap);
        ps.assignSlot(3, p.vanguard.quantityMap);
        ps.assignSlot(4, p.reinforcements.quantityMap);

        while (userPrompt.getInput() != "Start campaign")
        {
            ps.clearAndPrint("");
            userPrompt.ask("CAMPAIGNPREPLOOP", ".*");
            if (userPrompt.getInput() == "Choose equipment")
            {
                //ps.clearAndPrint("");
                //chooseFromInv("CHOOSEEQUIPMENT", equipment, playerInv);
                chooseFromQuantityInv("CHOOSEEQUIPMENT", equipmentInv, p.equipmentInv);
            }
            else if (userPrompt.getInput() == "Choose consumables")
            {
                //ps.clearAndPrint("");
                chooseFromQuantityInv("CHOOSECONSUMABLE", consumableInv, p.consumableInv);
            }
            else if (userPrompt.getInput() == "Choose your vanguard")
            {
                chooseFromDetailInv("SETVANGUARD", unitInv, p.vanguard);
            }
            else if (userPrompt.getInput() == "Choose your reinforcements")
            {
                chooseFromDetailInv("SETVANGUARD", unitInv, p.reinforcements);
            }
        }

    ps.clearAndPrint("Thank you!");

    return;
}
