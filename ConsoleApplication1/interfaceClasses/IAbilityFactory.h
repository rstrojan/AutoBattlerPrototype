#pragma once

#include <memory>
#include "../gameObjectClasses/GameObject.h"
#include "../gameObjectClasses/Base_IAbility.h"
#include "IAbility.h"


class IAbilityFactory
{
public:
	virtual std::shared_ptr<IAbility> makeIAbility(
		std::string key
		, std::shared_ptr<GameObject> owner) = 0;
};



