#include "Base_IAbility.h"


Base_IAbility::Base_IAbility(std::string key, std::shared_ptr<GameObject> owner)
    : GameObject(key)
    , owner(owner)
    , desc()
    , isHidden()
{
    Base_IAbility iabilityData;
    try
    {
        std::ifstream file("resources/jsonArchives/IAbility.json");
        cereal::JSONInputArchive archive(file);
        archive(cereal::make_nvp(key, iabilityData));
    }
    catch (const cereal::Exception& e)
    {
        std::cout << "Error loading IAbility: " << e.what() << std::endl;
        std::exit(1);
    }

    //
    for (auto const& x : iabilityData.tagKeyList)
        tags.emplace(std::make_pair(x, std::make_shared<GameObject>(*this)));

    this->desc = iabilityData.desc;
    this->isHidden = iabilityData.isHidden;
}

Base_IAbility::Base_IAbility(
    std::string name
    , std::string desc
    , bool isHidden
    , std::shared_ptr<GameObject> owner)
    : GameObject(name)
    , owner(owner)
    , desc(desc)
    , isHidden(isHidden)
{}


//NOT FOR NORMAL USE, this is for making a blank object to capture data when loading.
Base_IAbility::Base_IAbility()
    : GameObject()
    , owner()
    , desc()
    , isHidden()
{}

//NOT FOR NORMAL USE, this is to save off objects to the Ability json archive.
void Base_IAbility::save()
{
    std::fstream file;
    file.open("resources/jsonArchives/IAbility.json", std::ios::app);
    cereal::JSONOutputArchive archive(file);
    auto const objname = this->name;
    archive(cereal::make_nvp(objname, *this));
}