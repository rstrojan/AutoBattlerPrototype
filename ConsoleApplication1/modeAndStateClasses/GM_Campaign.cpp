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

//The choices give extra details based on the game objects choiceDetailString.
//Detailed view of the fromInv is displayed in the slots.
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

//Takes the player object and an action string of "ADD" or "REMOVE"
// Sub menu that prompts players to choose a unit, an item, and then add/remove
// the item to/from that unit. If action=="ADD", any current item is moved to 
// the players equipmentInv.
void GM_Campaign::equipVanguard(Player& p, std::string action)
{
    PrntScrn tempScrn;
    if (!p.vanguard.isEmpty() && !p.equipmentInv.isEmpty())
    {
        Prompt tempPrompt;
        tempScrn.assignSlots(p.vanguard.getSlotDetailMaps(), true);
        tempScrn.clearAndPrint("Choose a unit to manage their items.");
        std::string unitSelection = tempPrompt.ask("CHOOSEUNIT","NULL", p.vanguard.getDetailedChoiceVector());
        std::string selection;
        std::shared_ptr <Item> itemSelection;
        if (action == "ADD")
        {
            tempScrn.clearAndPrint("Choose an item to add to the selected unit.");
            selection = tempPrompt.ask("CHOOSEEQUIPMENT", "NULL", p.equipmentInv.getDetailedChoiceVector());
            itemSelection = std::dynamic_pointer_cast<Item> (p.equipmentInv.removeItem(selection));
        }
        else if (action == "REMOVE")
        {
            tempScrn.clearAndPrint("Choose an item to remove from the selected unit.");
            selection = tempPrompt.ask("CHOOSEEQUIPMENT", "NULL", { "Weapon", "Armor", "Trinket" });
        }

        //find the unit in the vanguard
        for (auto i : p.vanguard.inv)
        {
            if (i->name == unitSelection || i->getChoiceDetailString() == unitSelection)
            {
                //remove the item from the unit
                std::shared_ptr<GameObject> removedItem;
                if (action == "ADD")
                    removedItem = std::dynamic_pointer_cast<Unit>(i)->removeItem(itemSelection->type);
                else
                {
                    std::string type;
                    if (selection == "Weapon")
                        type = "WEAPON";
                    else if (selection == "Armor")
                        type = "ARMOR";
                    else if (selection == "Trinket")
                        type = "TRINKET";
                    removedItem = std::dynamic_pointer_cast<Unit>(i)->removeItem(type);
                }
                //add the item to the equipment inventory
                if (removedItem != NULL)
                {
                    p.equipmentInv.addItem(removedItem);
                }

                //add the item to the unit
                if (action == "ADD")
                    std::dynamic_pointer_cast<Unit>(i)->addItem(itemSelection);

                //NOTE, I don't like this being inside here, but has to be called
                // otherwise the slot maps won't update properly between loops.
                //Try to investigate further to see if it would be possible to NOT
                // have to call this. The whole scheme for slot detail maps might
                // need to be redone in order to do that.
                p.vanguard.getSlotDetailMaps();
                return;
            }
        }

    }
    else
    {
        tempScrn.print("One of the inventories are empty.\n");
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

        //takes a string of two ints up to two digits long, separated by a period and split them into two vars
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

//Sub menu for equiping units with items. This will be called from the preCombat loop.
void GM_Campaign::equipUnitMenu(Player& p)
{
    PrntScrn tempScrn;
    Prompt tempPrompt;
    tempScrn.assignSlots(p.vanguard.getSlotDetailMaps(), true);

    while (tempPrompt.getInput() != "Back to previous menu")
    {
        tempScrn.clearAndPrint("Above: " + p.vanguard.name + "\nBelow: " + p.equipmentInv.name + "\n");
        tempPrompt.ask("EQUIPUNITS01");
        if (tempPrompt.getInput() == "Equip a unit")
        {
            equipVanguard(p, "ADD");
        }
        else if (tempPrompt.getInput() == "Remove equipment from a unit")
        {
            equipVanguard(p, "REMOVE");
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
        else if (userPrompt.getInput() == "Equip Units")
        {
            equipUnitMenu(p);
        }
    }

    return;
}

//This takes a GameObject and a RuleSet, then checks if the
// GameObject's tagList meets the RuleSet's conditions.
// Will return true or false based on the RuleSet.
bool GM_Campaign::multiTagCheck(GameObject& obj, RuleSet& ruleSet)
{

    if (ruleSet.logOp == "AND")
    {
        for (auto r : ruleSet.ruleList)
        {
            if (!tagCheck(obj, (*r)))
                return false;
        }
        return true;
    }

    if (ruleSet.logOp == "OR")
        for (auto r : ruleSet.ruleList)
        {
            if (tagCheck(obj, (*r)))
                return true;
        }

    return false;
}

//This takes a GameObject and a Rule, the rule checks if the
// Tag count for the targetTag matches the ruleOp (rule operator)
// and returns a bool result
bool GM_Campaign::tagCheck(GameObject& obj, Rule rule)
{
    if (rule.ruleOp == "==")
        return obj.tagCount(rule.targetTag) == rule.count;
    if (rule.ruleOp == ">")
        return obj.tagCount(rule.targetTag) > rule.count;
    if (rule.ruleOp == ">=")
        return obj.tagCount(rule.targetTag) >= rule.count;
    if (rule.ruleOp == "<")
        return obj.tagCount(rule.targetTag) < rule.count;
    if (rule.ruleOp == "<=")
        return obj.tagCount(rule.targetTag) <= rule.count;
    
    return false;
}