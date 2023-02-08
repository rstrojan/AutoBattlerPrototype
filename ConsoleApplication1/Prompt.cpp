#include "Prompt.h"

Prompt::Prompt()
{
	entryFoundFlag = false;

}

//You can skip the optional validationCriteriaOverride by setting it's value to "NULL"
std::string Prompt::ask(std::string promptID, std::string validationCriteriaOverride, std::vector<std::string> choicesOverride)
{
	//make sure prompt is clear before using
	clearPrompt();
	//use promptID as lookup key
	promptKey = promptID;

	//open the file
	std::ifstream f;
	try
	{
		f.open("prompt.csv");
		if (!f)
			throw std::logic_error("Could not open prompt.csv.");
	}
	catch (const std::exception& e)
	{
		std::cerr << "Caught: " << e.what() << '\n';
		return "Error 01";
	}

	//if the file is opened, start checking for key
	std::string currLine;
	std::regex regKey("^" + promptKey);
	std::smatch match;
	while (std::getline(f, currLine))
	{
		if (std::regex_search(currLine,match,regKey))
		{
			storeMatch(currLine, validationCriteriaOverride, choicesOverride); 
			entryFoundFlag = true;
			continue;
		}
		//I should put in an escape clause here
		//for when the Prompt is full instead of
		//checking the full file.
	}
	try
	{
		if (entryFoundFlag == false)
			throw std::logic_error("No entry was found for key: " + promptKey);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Caught: " << e.what() << '\n';
		return "Error 02";
	}

	//Don't forget to close the file.
	f.close();

	//Check for overrides (I debate making these pointers instead of "NULL" string literals)
	if (validationCriteriaOverride != "NULL")
		validationCriteria = validationCriteriaOverride;
	if (choicesOverride[0] != "NULL")
		choices = choicesOverride;

	//Display Q to the player
	std::cout << promptText << '\n';

	//Start the input validation loop
	bool isValid = false; 
	do
	{
		//if multi, print out choices
		if (promptType == "multi")
		{
			std::cout << "(Enter the number that matches your choice.)\n";
			for (int i = 0; i < signed(choices.size()); i++)
				std::cout << (i + 1) << ") " << choices[i] << '\n';
		}

		//get the input
		std::cout << "> ";
		std::getline(std::cin, input);

		//prep to check input and exit
		std::smatch inputMatch;
		std::regex validationRegex(validationCriteria);
		std::regex exitCheckRegex("[eE][xX][iI][tT]");
		if (std::regex_match(input, inputMatch, exitCheckRegex))
		{
			std::cout << "You chose to exit. Goodbye.\n";
			std::exit(0);
		}
		else if(std::regex_match(input,inputMatch,validationRegex))
			isValid = true;
		if (isValid == false)
		{
			std::cout << invalidResponse << '\n';
			std::cout << "(Or type 'exit' to quit.)\n";
		}

	} while (isValid == false);

	return input;
}


//Call storeMatch when you find a valid entry to store it
//in the prompt object. 
void Prompt::storeMatch(std::string str, std::string &validationCriteriaOverride, std::vector<std::string> &choicesOverride)
{
	std::smatch entry;
	std::regex lineType;
	
	lineType = "\\.PROMPT,";
	if (std::regex_search(str, entry, lineType))
	{
		promptText = entry.suffix();
		return;
	}
	lineType = "\\.TYPE,";
	if (std::regex_search(str, entry, lineType))
	{
		promptType = entry.suffix();
		return;
	}
	lineType = "\\.VALIDATION,";
	if (std::regex_search(str, entry, lineType) && validationCriteriaOverride == "NULL")
	{
		validationCriteria = entry.suffix();
		return;
	}
	lineType = "\\.INVALIDRESPONSE,";
	if (std::regex_search(str, entry, lineType))
	{
		invalidResponse = entry.suffix();
		return;
	}
	lineType = "\\.CHOICE,";
	if (std::regex_search(str, entry, lineType) && choicesOverride[0] == "NULL")
	{
		choices.push_back(entry.suffix());
		return;
	}
	return;
}

std::string Prompt::getInput()
{

	return input;
}

void Prompt::clearPrompt()
{
	promptKey = "";
	promptText = "";
	promptType = "";
	validationCriteria = "";
	invalidResponse = "";
	choices.clear();
	input = "";
	entryFoundFlag = "";
}