#include "Rule.h"


Rule::Rule(std::string name, std::string targetTag, std::string ruleOp, int count)
	: GameObject(name)
	, count(count)
	, targetTag(targetTag)
	, ruleOp(ruleOp)
{};

//Takes a key and loads the rule from the Rule.json file
Rule::Rule(std::string key)
: GameObject(key)
{
	Rule ruleData;
	try
	{
		std::ifstream file("resources/jsonArchives/Rule.json");
		cereal::JSONInputArchive archive(file);
		archive(cereal::make_nvp(key, ruleData));
	}
	catch (const cereal::Exception& e)
	{
		std::cout << "Error loading Rule: " << e.what() << std::endl;
		std::exit(1);
	}
	this->count     = ruleData.count;
	this->targetTag = ruleData.targetTag;
	this->ruleOp    = ruleData.ruleOp;
}


//NOT FOR REGULAR USE, this is for making a blank object for cereal.
Rule::Rule()
	: GameObject("")
	, count()
	, targetTag()
	, ruleOp()
{};

//NOT FOR REGULAR USE, this is to save off objects to the Rule json archive.
void Rule::save()
{
	std::fstream file;
	file.open("resources/jsonArchives/Rule.json", std::ios::app);
	cereal::JSONOutputArchive archive(file);
	auto const objname = this->name;
	archive(cereal::make_nvp(objname, * this));
}