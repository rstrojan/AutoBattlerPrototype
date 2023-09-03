#include "GS_Campaign.h"

GS_Campaign::GS_Campaign() :
	prepLoopConsumablesInv("Consumables"),
	prepLoopEquipmentInv("Equipment"),
	prepLoopUnitInv("Units")
{
	//prepLoopEquipmentInv.addItem(std::shared_ptr<GameObject>(new Item("Sword", Item::itemType::WEAPON, 10, 0, 5, 0, {})), 8);
	//prepLoopEquipmentInv.addItem(std::shared_ptr<GameObject>(new Item("Shield", Item::itemType::ARMOR, 10, 0, 0, 5, {})), 8);
	//prepLoopEquipmentInv.addItem(std::shared_ptr<GameObject>(new Item("Ring", Item::itemType::TRINKET, 10, 5, 0, 0, {})), 8);
	prepLoopEquipmentInv.addItem(std::make_shared<Item>("Sword"), 10);
	prepLoopEquipmentInv.addItem(std::make_shared<Item>("Shield"), 10);
	prepLoopEquipmentInv.addItem(std::make_shared<Item>("Ring"), 10);

	prepLoopConsumablesInv.addItem(std::make_shared<Consumable>("Hearty Meal"), 20);
	prepLoopConsumablesInv.addItem(std::make_shared<Consumable>("Quick Snack"), 20);

	prepLoopUnitInv.addItem(std::make_shared<Unit>("James"));
	prepLoopUnitInv.addItem(std::make_shared<Unit>("Ryan"));
	prepLoopUnitInv.addItem(std::make_shared<Unit>("Thomas"));
	prepLoopUnitInv.addItem(std::make_shared<Unit>("Nicole"));
	prepLoopUnitInv.addItem(std::make_shared<Unit>("Jacob"));
	prepLoopUnitInv.addItem(std::make_shared<Unit>("Jeremy"));

};

