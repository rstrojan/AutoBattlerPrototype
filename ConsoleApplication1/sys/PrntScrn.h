#pragma once
#include <regex>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class PrntScrn
{
	static std::vector<std::map<std::string, std::string>> slots;
	std::string linebreak;
	std::map<std::string, std::string>* slotOne;
	std::map<std::string, std::string>* slotTwo;
	std::map<std::string, std::string>* slotThree;
	std::map<std::string, std::string>* slotFour;
	std::map<std::string, std::string>* slotFive;
	std::map<std::string, std::string> blankMap = { { "","" } };
	const int slotWidth = 15;

public:
	PrntScrn();
	void print(std::string str);
	void clearAndPrint(std::string str);
	void assignSlot(int slotNumber, std::map<std::string, std::string>& map);
	void assignSlots(std::vector<std::map<std::string, std::string>>& maps);

private:
	std::vector<std::string> formatSlot(std::map<std::string, std::string>* map);
	void printHud();

};

