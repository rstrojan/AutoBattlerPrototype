#pragma once
#include <vector>
#include <string>
#include <map>
#include <memory>

#include "gameObjectClasses/GameObject.h"

class Inventory
{
public:
	std::string name;
	//std::vector <GameObject*> inv;
	std::vector <std::shared_ptr<GameObject>> inv;
	std::map <std::string, std::string> quantityMap;


public:
	Inventory(std::string name);
	Inventory(std::string name, int maxSize);
	void addItem(std::shared_ptr<GameObject> obj, int quantity = 1);
	void removeItem(std::shared_ptr<GameObject> obj);
	void removeItem(std::string itemName);
	static void transferItem(std::string itemName, Inventory& fromInv, Inventory& toInv);
	std::vector<std::string>& getDetailedChoiceVector();
	std::vector<std::string>& getQuantityChoiceVector();
	std::vector<std::map<std::string, std::string>>& getSlotDetailMaps();
	bool isEmpty();
	bool isFull();
	bool hasMaxSize();
	int setMaxSize(int size);
	int getMaxSize();
	int getCurrSize();
	void clearSize();

private:
	int maxSize;
	std::vector<std::string> detailedChoiceVector;
	std::vector<std::string> quantityChoiceVector;
	std::vector<std::map<std::string, std::string>> slotDetailMaps;

	void updateQuantityMap();
	void updateDetailedChoiceVector();
	void updateQuantityChoiceVector();
	void updateSlotDetailMaps();
};

