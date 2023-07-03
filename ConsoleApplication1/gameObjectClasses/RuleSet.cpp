#include "RuleSet.h"

RuleSet::RuleSet(std::string name, std::string logOp, std::vector<std::shared_ptr<Rule>> ruleList)
	: GameObject(name),
	logOp(logOp),
	ruleList(ruleList)
{}

//Takes a key and loads the object from the json archive.
RuleSet::RuleSet(std::string key)
	: GameObject(key),
	logOp(),
	ruleList()
{
	RuleSet ruleSetData;
	try
	{
		std::fstream file;
		file.open("resources/jsonArchives/RuleSet.json");
		cereal::JSONInputArchive archive(file);
		archive(cereal::make_nvp(key, ruleSetData));
	}
	catch (const cereal::Exception& e)
	{
			std::cout << "Error loading RuleSet: " << e.what() << std::endl;
				std::exit(1);
	}
	for (auto const& rule : ruleSetData.ruleKeyList)
		this->ruleList.push_back(std::make_shared<Rule>(rule));

	this->logOp = ruleSetData.logOp;
}

//NOT FOR REGULAR USE, this is for making a blank object for cereal.
RuleSet::RuleSet()
	: GameObject(""),
	logOp(),
	ruleList()
{}

//NOT FOR REGULAR USE, this is to save off objects to the RuleSet json archive.
void RuleSet::save()
{
	std::fstream file;
	file.open("resources/jsonArchives/RuleSet.json", std::ios::app);
	cereal::JSONOutputArchive archive(file);
	auto const objname = this->name;
	archive(cereal::make_nvp(objname, * this));
}