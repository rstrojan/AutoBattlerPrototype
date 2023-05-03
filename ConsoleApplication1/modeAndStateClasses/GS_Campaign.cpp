#include "GS_Campaign.h"

GS_Campaign::GS_Campaign() :
	prepLoopConsumablesInv("Consumables"),
	prepLoopEquipmentInv("Equipment"),
	prepLoopUnitInv("Units")
{
	prepLoopEquipmentInv.addItem(std::shared_ptr<GameObject>(new Item("Sword", Item::itemType::WEAPON, 10, 0, 5, 0, {})), 8);
	prepLoopEquipmentInv.addItem(std::shared_ptr<GameObject>(new Item("Shield", Item::itemType::ARMOR, 10, 0, 0, 5, {})), 8);
	prepLoopEquipmentInv.addItem(std::shared_ptr<GameObject>(new Item("Ring", Item::itemType::TRINKET, 10, 5, 0, 0, {})), 8);


	prepLoopConsumablesInv.addItem(std::shared_ptr<GameObject>(new GameObject("Hearty Meal")), 20);
	prepLoopConsumablesInv.addItem(std::shared_ptr<GameObject>(new GameObject("Quick Snack")), 20);


	std::shared_ptr<Unit> test(new Unit("James", "mouse", 10, 1, 0));
	std::shared_ptr<Unit> test1(new Unit("Ryan", "mouse", 10, 1, 0));
	std::shared_ptr<Unit> test2(new Unit("Thom", "mouse", 10, 1, 0));
	std::shared_ptr<Unit> test3(new Unit("Bonnie", "bird", 8, 1, 0));
	std::shared_ptr<Unit> test4(new Unit("Sheryl", "bird", 8, 1, 0));
	std::shared_ptr<Unit> test5(new Unit("Doug", "bird", 8, 1, 0));
	prepLoopUnitInv.addItem(test);
	prepLoopUnitInv.addItem(test1);
	prepLoopUnitInv.addItem(test2);
	prepLoopUnitInv.addItem(test3);
	prepLoopUnitInv.addItem(test4);
	prepLoopUnitInv.addItem(test5);
};

