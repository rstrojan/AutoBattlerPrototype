#include "GM_Campaign.h"

GM_Campaign::GM_Campaign() {};

//Prompts via a promptKey lookup and provides a list of choices from the fromInv,
//then allows user to set how much of their selection to be transferred to the 
//toInv.
void GM_Campaign::chooseFromQuantityInv(std::string promptKey, Inventory& fromInv, Inventory& toInv)
{
    PrntScrn tempScrn;
    if (!fromInv.isEmpty())
    {
        Prompt tempPrompt;
        tempScrn.assignSlot(1, fromInv.quantityMap);
        tempScrn.assignSlot(3, toInv.quantityMap);
        tempScrn.clearAndPrint("");
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
        tempScrn.print("The inventory you are trying to select from is empty.\n");
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
    if (!fromInv.isEmpty())
    {
        Prompt tempPrompt;

        tempScrn.assignSlots(toInv.getSlotDetailMaps(), true);
        tempScrn.clearAndPrint("");
        std::vector<std::string> fromInvChoices = fromInv.getDetailedChoiceVector();

        //first have the player pick the item and store the selection
        std::string selection = tempPrompt.ask(promptKey, "NULL", fromInvChoices);

        //call transfer
        Inventory::transferItem(selection, fromInv, toInv);
    }
    else
    {
        tempScrn.print("The inventory you are trying to select from is empty.\n");
        system("pause");
    }


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
    

        //construct player and game state
        Player p("Player One");
        GS_Campaign gs;


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
