#pragma once
#include <memory>
#include "../modeAndStateClasses/GS_Campaign.h"


class GS_Campaign;
class IAbility
{
public:

    virtual void update(GS_Campaign& currGS) = 0; //THE GS SHOULD BE MADE GENERIC
    /*this is what all of the abilities have in common.
     When update is called, each ability will update it's eventHandler.
     removing/subscribing itself to events as needed based on the game state.
      The event handlers will handle it from there. Each event handler will
      go through the same basic steps:
      1) Validation: They'll take some extra criteria to see if they should
      execute or not. The info could be about the event that triggered, it could
      be info from the game state, or perhaps a tag check on the owner of the ability.
      2) Execution: If the validation passes, the event handler will execute the ability.
    */

    virtual std::string getName() = 0;


};
