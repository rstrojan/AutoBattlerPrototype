#include "GS_Campaign.h"

GS_Campaign::GS_Campaign() :
	prepLoopConsumablesInv("Consumables"),
	prepLoopEquipmentInv("Equipment"),
	prepLoopUnitInv("Units")
{
	GameObject* sword = new GameObject("Sword");
	GameObject* spear = new GameObject("Spear");
	GameObject* shield = new GameObject("Shield");
	prepLoopEquipmentInv.addItem(sword, 8);
	prepLoopEquipmentInv.addItem(spear, 8);
	prepLoopEquipmentInv.addItem(shield, 8);

	GameObject* heartyMeal = new GameObject("Hearty Meal");
	GameObject* quickSnack = new GameObject("Quick Snack");
	prepLoopConsumablesInv.addItem(heartyMeal, 20);
	prepLoopConsumablesInv.addItem(quickSnack, 20);

	GameObject* mouse01 = new GameObject("James");
	GameObject* mouse02 = new GameObject("Ryan");
	GameObject* mouse03 = new GameObject("Thom");
	GameObject* mouse04 = new GameObject("Doug");
	GameObject* mouse05 = new GameObject("Sheryl");
	GameObject* mouse06 = new GameObject("Bonnie");
	prepLoopUnitInv.addItem(mouse01);
	prepLoopUnitInv.addItem(mouse02);
	prepLoopUnitInv.addItem(mouse03);
	prepLoopUnitInv.addItem(mouse04);
	prepLoopUnitInv.addItem(mouse05);
	prepLoopUnitInv.addItem(mouse06);
};

