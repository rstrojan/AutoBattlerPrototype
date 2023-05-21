#include "PrntScrn.h"


PrntScrn::PrntScrn()
{
	slotOne;
	slotTwo;
	slotThree;
	slotFour;
	slotFive;
	linebreak.assign(80, '~');
	assignSlot(1, blankMap);
	assignSlot(2, blankMap);
	assignSlot(3, blankMap);
	assignSlot(4, blankMap);
	assignSlot(5, blankMap);

}

//basic print function
void PrntScrn::print(std::string str)
{
	std::cout << str;
}

//clears console, reprints slots, and then
//prints str
void PrntScrn::clearAndPrint(std::string str)
{
	system("CLS");
	printHud();
	print(str);
	return;
}

//prints the slots to console
void PrntScrn::printHud()
{

	//load the maps to string vectors.
	std::vector <std::string> formattedSlotOne = formatSlot(slotOne);
	std::vector <std::string> formattedSlotTwo = formatSlot(slotTwo);
	std::vector <std::string> formattedSlotThree = formatSlot(slotThree);
	std::vector <std::string> formattedSlotFour = formatSlot(slotFour);
	std::vector <std::string> formattedSlotFive = formatSlot(slotFive);

	//Top line of slot hud
	std::cout << linebreak << '\n';

	//loop over the maps and print in slot format
	for (auto i = 0; i < 10; i++)
	{
		std::string buff;
		if (i < formattedSlotOne.size())
		{
			std::cout << formattedSlotOne[i];
			buff.assign(slotWidth - formattedSlotOne[i].size(), ' ');
			std::cout << buff << '|';
		}
		else
			std::cout << buff.assign(slotWidth, ' ') << '|';

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

	//bottom line of slot hud.
	std::cout << linebreak << '\n';

	return;
}

std::vector<std::string> PrntScrn::formatSlot(slot &s)
{
	std::vector <std::string> formatted;
	int i = 0;
	for (auto const& x : *s.map)
	{
		if (x.first == "title")
			formatted.insert(formatted.begin(), x.second + ((slotWidth - x.second.size()), '*'));
		else
		{
			if (s.isValueOnly)
			{
				formatted.push_back(x.second);
			}
			else
				formatted.push_back(x.first + ": " + x.second);
		}
		i++;
	}
	return formatted;
}


//Takes a reference to a map of string key/value pairs
//and assigns it a pointer for the given slot number
//maps with a key of "title" will have that entry 
//printed at the top line.
void PrntScrn::assignSlot(int slotNumber, std::map<std::string, std::string>& map, bool isValueOnly)
{
	if (slotNumber == 1)
		setSlot(slotOne, map, isValueOnly);
	else if (slotNumber == 2)
		setSlot(slotTwo, map, isValueOnly);
	else if (slotNumber == 3)
		setSlot(slotThree, map, isValueOnly);
	else if (slotNumber == 4)
		setSlot(slotFour, map, isValueOnly);
	else if (slotNumber == 5)
		setSlot(slotFive, map, isValueOnly);

	return;
}

//Takes a list of maps and assigns them to the PrntScrn slots in
//order from left to right.
void PrntScrn::assignSlots(std::vector<std::map<std::string, std::string>>& maps, bool isValueOnly)
{
	int slotNum = 1;
	for (auto& x : maps)
	{
		assignSlot(slotNum, x, isValueOnly);
		slotNum++;
	}
}

PrntScrn::slot PrntScrn::setSlot(slot &s, std::map<std::string, std::string>& map, bool isValueOnly)
{

	s.map = &map;
	s.isValueOnly = isValueOnly;

	return s;
}