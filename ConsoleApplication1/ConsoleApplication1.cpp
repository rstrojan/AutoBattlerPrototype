// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "sys/Prompt.h"
#include "sys/PrntScrn.h"
#include "modeAndStateClasses/GM_Campaign.h"


void printBreak()
{
    std::cout << "\n~~~~~~~~~\n\n";
    return;

}


int main()
{
    GM_Campaign newCampaign;

    newCampaign.prepLoop();

    newCampaign.preCombatLoop();

}
