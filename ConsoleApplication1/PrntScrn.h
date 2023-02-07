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
	std::map<std::string, std::string> *slotOne;
	std::map<std::string, std::string> *slotTwo;
	std::map<std::string, std::string> *slotThree;
	std::map<std::string, std::string> *slotFour;
	std::map<std::string, std::string> *slotFive;
	int slotWidth;

	public:
	PrntScrn();
	void print(std::string str);
	void clearAndPrint(std::string str);
	void assignSlot(int slotNumber, std::map<std::string, std::string>& map);

	private:
	std::vector<std::string> formatSlot(std::map<std::string, std::string> *map);
	void printHud();

};

PrntScrn::PrntScrn()
{
	linebreak.assign( 80, '~');
	slotWidth = 15;
	
}

void PrntScrn::print(std::string str)
{
	std::cout << str;
}

void PrntScrn::clearAndPrint(std::string str)
{
	system("CLS");
	printHud();
	print(str);
	return;
}

void PrntScrn::printHud()
{
	std::cout << linebreak << '\n';
	//load the maps to string vectos.

	std::vector <std::string> formattedSlotOne = formatSlot(slotOne);
	std::vector <std::string> formattedSlotTwo = formatSlot(slotTwo);
	std::vector <std::string> formattedSlotThree = formatSlot(slotThree);
	std::vector <std::string> formattedSlotFour = formatSlot(slotFour);
	std::vector <std::string> formattedSlotFive = formatSlot(slotFive);


	for (int i = 0; i < 10; i++)
	{
		std::string buff;
		if (i < formattedSlotOne.size())
		{
			std::cout << formattedSlotOne[i];
			buff.assign(slotWidth - formattedSlotOne[i].size(), ' ');
			std::cout << buff << '|';
		}
		else
			std::cout << buff.assign(slotWidth,' ') << '|';

		if (i < formattedSlotTwo.size())
		{
			std::cout << formattedSlotTwo[i];
			buff.assign(slotWidth - formattedSlotTwo[i].size(), ' ');
			std::cout << buff << '|';
		}
		else
			std::cout << buff.assign(slotWidth, ' ') << '|';

		if (i < formattedSlotThree.size())
		{
			std::cout << formattedSlotThree[i];
			buff.assign(slotWidth - formattedSlotThree[i].size(), ' ');
			std::cout << buff << '|';
		}
		else
			std::cout << buff.assign(slotWidth, ' ') << '|';

		if (i < formattedSlotFour.size())
		{
			std::cout << formattedSlotFour[i];
			buff.assign(slotWidth - formattedSlotFour[i].size(), ' ');
			std::cout << buff << '|';
		}
		else
			std::cout << buff.assign(slotWidth, ' ') << '|';

		if (i < formattedSlotFive.size())
		{
			std::cout << formattedSlotFive[i];
			buff.assign(slotWidth - formattedSlotFive[i].size(), ' ');
			std::cout << buff << '|';
		}
		else
			std::cout << buff.assign(slotWidth, ' ') << '|';

		std::cout << '\n';
	}

	std::cout << linebreak << '\n';
	return;
}



std::vector<std::string> PrntScrn::formatSlot(std::map<std::string, std::string> *map)
{
	std::vector <std::string> formatted;
	int i = 0;	for (auto const& x : *map)
	{
		if (x.first == "title")
			formatted.insert(formatted.begin(), x.second + ((slotWidth - x.second.size()), '*'));
		else
			formatted.push_back(x.first + ": " + x.second);
		i++;
	}
	return formatted;
}

void PrntScrn::assignSlot(int slotNumber, std::map<std::string, std::string>& map)
{
	if (slotNumber == 1)
		slotOne = &map;
	else if (slotNumber == 2)
		slotTwo = &map;
	else if (slotNumber == 3)
		slotThree = &map;
	else if (slotNumber == 4)
		slotFour = &map;
	else if (slotNumber == 5)
		slotFive = &map;

	return;
}
