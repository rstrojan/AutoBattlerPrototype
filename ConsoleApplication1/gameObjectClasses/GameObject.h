#pragma once
#include <string>
#include <map>
#include <memory>


class GameObject
{
public:
	std::string name;

	GameObject(std::string name);
	std::string getChoiceDetailString();
	std::map<std::string, std::string>& getSlotDetailMap();

protected:
	std::string choiceDetailString;
	std::map<std::string, std::string> slotDetailMap;

	void virtual generateChoiceDetailString();
	void virtual generateSlotDetailMap();
	
};

