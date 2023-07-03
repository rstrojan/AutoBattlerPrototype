#include "Consumable.h"

Consumable::Consumable(std::string name, consumableType type, std::vector<std::shared_ptr<Buff>> buffList) :
    GameObject(name),
    type(type),
    buffList(buffList)
{}

//Takes a key and loads the object from the json archive.
Consumable::Consumable(std::string key) :
    GameObject(key),
    type(),
    ruleSet(),
    buffList()
{
    Consumable consumableData;
    try
    {
        std::ifstream file("resources/jsonArchives/Consumable.json");
        if (file.fail())
            std::cout << "fail\n";
        cereal::JSONInputArchive archive(file);
        archive(cereal::make_nvp(key, consumableData));
    }
    catch (const cereal::Exception& e)
    {
        std::cout << "Error loading Consumable: " << e.what() << std::endl;
        std::exit(1);
    }
    for (auto const& buff : consumableData.buffKeyList)
        buffList.emplace_back(std::make_shared<Buff>(buff));
    for (auto const& tag : consumableData.tagKeyList)
        tags.emplace(std::make_pair(tag, std::make_shared<GameObject>(*this)));
    this->type = consumableData.type;
    this->ruleSet = std::make_shared<RuleSet>(consumableData.ruleSetKey);
}

//NOT FOR REGULAR USE, this is for making a blank object for cereal.
Consumable::Consumable() :
    GameObject(""),
    type(),
    ruleSet(),
    buffList()
{}

//NOT FOR REGULAR USE, this is to save off objects to the Consumable json archive.
void Consumable::save()
{
    std::fstream file;
    file.open("resources/jsonArchives/Consumable.json", std::ios::app);
    cereal::JSONOutputArchive archive(file);
    auto const objname = this->name;
    archive(cereal::make_nvp(objname, * this));
}