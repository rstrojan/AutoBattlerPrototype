#pragma once
#include <regex>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cereal/types/memory.hpp>

class PrntScrn
{
	static std::vector<std::map<std::string, std::string>> slots;
	std::string linebreak;
	std::map<std::string, std::string> blankMap = { { "","" } };
	const int slotWidth = 15;

	struct slot {
		std::map<std::string, std::string>* map;
		bool isValueOnly;
	};

	slot slotOne;
	slot slotTwo;
	slot slotThree;
	slot slotFour;
	slot slotFive;


public:
	PrntScrn();
	void print(std::string str);
	void clearAndPrint(std::string str);
	void assignSlot(int slotNumber, std::map<std::string, std::string>& map, bool isValueOnly = false);
	void assignSlots(std::vector<std::map<std::string, std::string>>& maps, bool isValueOnly = false);

private:
	void printHud();
	std::vector <std::string> formatSlot(slot &s);
	slot setSlot(slot &s, std::map<std::string, std::string>& map, bool isValueOnly);

};

