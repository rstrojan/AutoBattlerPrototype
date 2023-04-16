#include "GM_Campaign.h"

GM_Campaign::GM_Campaign() :
    p("Player One")
{
    ps.assignSlot(1, p.vanguard.quantityMap);
    ps.assignSlot(2, p.reinforcements.quantityMap);
    ps.assignSlot(3, p.equipmentInv.quantityMap);
    ps.assignSlot(4, p.consumableInv.quantityMap);

};

//Prompts via a promptKey lookup and provides a list of choices from the fromInv,
//then allows user to set how much of their selection to be transferred to the 
//toInv.
void GM_Campaign::chooseFromQuantityInv(std::string promptKey, Inventory& fromInv, Inventory& toInv)
{
    PrntScrn tempScrn;
    if (!fromInv.isEmpty() && !toInv.isFull())
    {
        Prompt tempPrompt;
        tempScrn.assignSlot(1, fromInv.quantityMap);
        tempScrn.assignSlot(3, toInv.quantityMap);
        tempScrn.clearAndPrint("Above Inv: " + fromInv.name + "\nBelow Inv: " + toInv.name + "\n");
        std::vector<std::string> fromInvChoices = fromInv.getQuantityChoiceVector();

        //first have the player pick the item and store the selection
        std::string selection = tempPrompt.ask(promptKey, "NULL", fromInvChoices);

        //pick the quantity and validate
        do { tempPrompt.ask("HOWMANY", "\\d+"); } while (0 > (stoi(fromInv.quantityMap[selection]) - stoi(tempPrompt.getInput())));

        //call transfer a number of times equal to the entered quantity
        for (int i = 0; i < std::stoi(tempPrompt.getInput()); i++)
            Inventory::transferItem(selection, fromInv, toInv);
    }
    else
    {
        if (fromInv.isEmpty())
            tempScrn.print("The inventory you are trying to select from is empty.\n");
        if (toInv.isFull())
            tempScrn.print("The inventory you are trying to add to is full.\n");
        system("pause");
    }


    return;
}


//Prompts via a promptKey lookup and provies a list of choices from the fromInv,
//The choices give extra details based on the game objects choiceDetailString.
//Detailed view of the toInv is displayed in the slots.
void GM_Campaign::chooseFromDetailInv(std::string promptKey, Inventory& fromInv, Inventory& toInv)
{
    PrntScrn tempScrn;
    if (!fromInv.isEmpty() && !toInv.isFull())
    {
        Prompt tempPrompt;

        tempScrn.assignSlots(toInv.getSlotDetailMaps(), true);
        tempScrn.clearAndPrint("Above Inv: " + fromInv.name + "\nBelow Inv: " + toInv.name + "\n");
        std::vector<std::string> fromInvChoices = fromInv.getDetailedChoiceVector();
        fromInvChoices.push_back("Cancel");
        //first have the player pick the item and store the selection
        std::string selection = tempPrompt.ask(promptKey, "NULL", fromInvChoices);
        if (tempPrompt.getInput() != "Cancel")
        {
            //call transfer
            Inventory::transferItem(selection, fromInv, toInv);
        }
    }
    else
    {
        if (fromInv.isEmpty())
            tempScrn.print("The inventory you are trying to select from is empty.\n");
        if (toInv.isFull())
            tempScrn.print("The inventory you are trying to add to is full.\n");
        system("pause");
    }


    return;
}

//Prompts via a promptKey lookup and provies a list of choices from the fromInv,
//The choices give extra details based on the game objects choiceDetailString.
//Detailed view of the toInv is displayed in the slots.
void GM_Campaign::removeFromDetailInv(Inventory& fromInv)
{
    PrntScrn tempScrn;
    if (!fromInv.isEmpty())
    {
        Prompt tempPrompt;
        tempScrn.assignSlots(fromInv.getSlotDetailMaps(), true);
        tempScrn.clearAndPrint("Inv Name: " + fromInv.name + "\n");
        std::vector<std::string> fromInvChoices = fromInv.getDetailedChoiceVector();
        fromInvChoices.push_back("Cancel");
        //first have the player pick the item and store the selection
        std::string selection = tempPrompt.ask("REMOVEFROMINV", "NULL", fromInvChoices);
        if (tempPrompt.getInput() != "Cancel")
        {
            //call transfer
            fromInv.removeItem(selection);
        }
    }
    else
    {
        tempScrn.print("The inventory you are trying to select from is empty.\n");
        system("pause");
    }
}


//Prompts user to enter two ints that represent the position of two items
// in an inventory. It then swaps the position of those items in the inventory
void GM_Campaign::swapItemsInDetailInv(Inventory& inv)
{
    PrntScrn tempScrn;
    if (!inv.isEmpty())
    {
        Prompt tempPrompt;
        tempScrn.assignSlots(inv.getSlotDetailMaps(), true);
        tempScrn.clearAndPrint("Inv Name: " + inv.name + "\n");

        std::string selection = tempPrompt.ask("MANAGEUNITS02");

        //takes a string of two ints up to two digits long, separated by a comma and split them into two vars
        if (selection.find(".") != std::string::npos)
        {
            int perPos = selection.find(".");
            int itemPos1 = stoi(selection.substr(0, perPos));
            int itemPos2 = stoi(selection.substr(perPos + 1, selection.length() - 1));

            inv.swapItems(itemPos1, itemPos2);
        }
    }
    else
    {
        tempScrn.print("The inventory is empty.\n");
        system("pause");
    }
}


//This is temporarily overloaded with functionality that will be removed.
//The welcome prompt and instantiations will be removed.
void GM_Campaign::prepLoop()
{

    std::cout << "***************\n"
        << "Welcome to my game mock up. First up we're coming to the \n"
        << "Campaign Prep Loop, which is where the player chooses what \n"
        << "they're going to bring with them on their battles.\n"
        << "Ideally, players will bring along a few of each of the\n"
        << "supplies. They can't take everything, and that's ok because\n"
        << "they will get loot out on the battle fields.\n\n";

    //Player must choose start new game.
        userPrompt.ask("STARTMENU", "New Game");

        while (userPrompt.getInput() != "Start campaign")
        {
            ps.clearAndPrint("");
            userPrompt.ask("CAMPAIGNPREPLOOP", ".*");
            if (userPrompt.getInput() == "Choose equipment")
            {
                //ps.clearAndPrint("");
                //chooseFromInv("CHOOSEEQUIPMENT", equipment, playerInv);
                chooseFromQuantityInv("CHOOSEEQUIPMENT", gs.prepLoopEquipmentInv, p.equipmentInv);
            }
            else if (userPrompt.getInput() == "Choose consumables")
            {
                //ps.clearAndPrint("");
                chooseFromQuantityInv("CHOOSECONSUMABLE", gs.prepLoopConsumablesInv, p.consumableInv);
            }
            else if (userPrompt.getInput() == "Choose your vanguard")
            {
                chooseFromDetailInv("SETVANGUARD", gs.prepLoopUnitInv, p.vanguard);
            }
            else if (userPrompt.getInput() == "Choose your reinforcements")
            {
                chooseFromDetailInv("SETVANGUARD", gs.prepLoopUnitInv, p.reinforcements);
            }
        }

    ps.clearAndPrint("Thank you!");

    return;

}

//Sub menu for managing units. This will be called from the preCombatLoop.
void GM_Campaign::manageUnitMenu(Player& p)
{
    Prompt tempPrompt;
    PrntScrn tempScrn;
    tempScrn.assignSlot(1, p.vanguard.quantityMap);
    tempScrn.assignSlot(2, p.reinforcements.quantityMap);
    tempScrn.assignSlot(3, p.equipmentInv.quantityMap);
    tempScrn.assignSlot(4, p.consumableInv.quantityMap);
    
    while (tempPrompt.getInput() != "Back to previous menu")
    {
        tempScrn.clearAndPrint("");
        tempPrompt.ask("MANAGEUNITS01");
        if (tempPrompt.getInput() == "Swap two vanguard units")
        {
            swapItemsInDetailInv(p.vanguard);
        }
        else if (tempPrompt.getInput() == "Add to vanguard")
        {
            chooseFromDetailInv("SETVANGUARD", p.reinforcements, p.vanguard);
        }
        else if (tempPrompt.getInput() == "Remove from vanguard")
        {
            chooseFromDetailInv("SETVANGUARD", p.vanguard, p.reinforcements);
        }
        else if (tempPrompt.getInput() == "Remove from reinforcements")
        {
            removeFromDetailInv(p.reinforcements);
        }
    }

}

// The menu loop that the player will navigate before choosing a node and 
// starting combat phase. Player will use this menu to manage units and
// resources and also view and select the next node.
void GM_Campaign::preCombatLoop()
{

    ps.clearAndPrint("");


    while (userPrompt.getInput() != "Choose Node")
    {
        ps.clearAndPrint("");
        userPrompt.ask("PRECOMBAT");
        if (userPrompt.getInput() == "Manage Units")
        {
            manageUnitMenu(p);
		}
    }

    return;
}
