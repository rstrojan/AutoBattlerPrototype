#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cereal/types/string.hpp>
#include <regex>
#include <cereal/types/vector.hpp>


class Prompt
{
	std::string promptKey;
	std::string promptText;
	std::string promptType;
	std::string validationCriteria;
	std::string invalidResponse;
	std::vector<std::string> choices;
	std::string input;
	bool entryFoundFlag;

public:
	Prompt();
	std::string ask(std::string promptID, std::string validationCriteriaOverride = "NULL", std::vector<std::string> choicesOverride = { "NULL" });
	std::string getInput();

private:
	void storeMatch(std::string str, std::string& validationCriteriaOverride, std::vector<std::string>& choicesOverrid);
	void clearPrompt();
};