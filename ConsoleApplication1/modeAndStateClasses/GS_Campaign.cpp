#include "GS_Campaign.h"

GS_Campaign::GS_Campaign() :
	prepLoopConsumablesInv("Consumables"),
	prepLoopEquipmentInv("Equipment"),
	prepLoopUnitInv("Units")
{
	prepLoopEquipmentInv.addItem(std::shared_ptr<GameObject>(new GameObject("Sword")), 8);
	prepLoopEquipmentInv.addItem(std::shared_ptr<GameObject>(new GameObject("Spear")), 8);
	prepLoopEquipmentInv.addItem(std::shared_ptr<GameObject>(new GameObject("Shield")), 8);

	prepLoopConsumablesInv.addItem(std::shared_ptr<GameObject>(new GameObject("Hearty Meal")), 20);
	prepLoopConsumablesInv.addItem(std::shared_ptr<GameObject>(new GameObject("Quick Snack")), 20);

	prepLoopUnitInv.addItem(std::shared_ptr<GameObject>(new GameObject("James")));
	prepLoopUnitInv.addItem(std::shared_ptr<GameObject>(new GameObject("Ryan")));
	prepLoopUnitInv.addItem(std::shared_ptr<GameObject>(new GameObject("Thom")));
	prepLoopUnitInv.addItem(std::shared_ptr<GameObject>(new GameObject("Bonnie")));
	prepLoopUnitInv.addItem(std::shared_ptr<GameObject>(new GameObject("Sheryl")));
	prepLoopUnitInv.addItem(std::shared_ptr<GameObject>(new GameObject("Doug")));
};

