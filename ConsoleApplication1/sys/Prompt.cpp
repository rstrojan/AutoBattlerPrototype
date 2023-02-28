#include "Prompt.h"

Prompt::Prompt()
{
	entryFoundFlag = false;
	input = "";
}
//Takes promptId and uses it to find a correlating Prompt entry.
//The prompt is parsed from the file and presented to the user.
//Once the user input is validated, the input is returned.
//In multi type questions, the string value (not numerical value) is returned.
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
		f.open("resources/prompt/prompt.csv");
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

	//Check for overrides
	if (validationCriteriaOverride != "NULL")
		validationCriteria = validationCriteriaOverride;
	if (choicesOverride[0] != "NULL")
		choices = choicesOverride;

	//Display Q to the player
	std::cout << promptText << '\n';

	//Start the input validation loop
	bool isValid = false; //to hold the validation result
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

		//prep to check input and exit command
		std::smatch inputMatch;
		bool invalidMultiResponseFlag = false;
		std::regex validationRegex(validationCriteria);
		std::regex exitCheckRegex("[eE][xX][iI][tT]");
		if (std::regex_match(input, inputMatch, exitCheckRegex))
		{
			std::cout << "You chose to exit. Goodbye.\n";
			std::exit(0);
		}

		//if multi, convert to equivelant choice string
		if (promptType == "multi")
		{
			int inputInt;
			try
			{
				inputInt = stoi(input);
				//using .at() because it has bounds checking
				input = choices.at(inputInt - 1);
			}
			catch (const std::exception& e)
			{
				invalidMultiResponseFlag = true;
			}
		}

		if (std::regex_match(input, inputMatch, validationRegex) && !invalidMultiResponseFlag)
		{
			isValid = true;
		}

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

//Returns the latest input from the user.
std::string Prompt::getInput()
{
	return input;
}

//Clears all data from the Prompt so it can be resused
// without worrying about artifacts from previous uses.
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
