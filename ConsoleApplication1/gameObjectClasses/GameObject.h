#pragma once
#include <string>
#include <map>

class GameObject
{
public:
	std::string name;

	GameObject(std::string name);
	std::string getChoiceDetailString();
	std::map<std::string, std::string>& getSlotDetailMap();

private:
	std::string choiceDetailString;
	std::map<std::string, std::string> slotDetailMap;

	void generateChoiceDetailString();
	void generateSlotDetailMap();
	
};

