#pragma once
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/archives/json.hpp>
#include <fstream>
#include <iostream>
#include <cmath>


class GameObject
{
public:
	//Basic attributes
	std::string name;
	std::multimap<std::string, std::shared_ptr<GameObject>> tags;

	//Constructors
	GameObject(std::string name);
	GameObject();

	//Basic methods
	std::string getChoiceDetailString();
	std::map<std::string, std::string>& getSlotDetailMap();
	void addTags(std::multimap<std::string, std::shared_ptr<GameObject>> tagsToAdd);
	void removeTags(std::multimap<std::string, std::shared_ptr<GameObject>> tagsToRemove);
	int tagCount(std::string tag);


protected:
	std::string choiceDetailString;
	std::map<std::string, std::string> slotDetailMap;
	void virtual generateChoiceDetailString();
	void virtual generateSlotDetailMap();


	// For serialization
	void virtual save();
	friend class cereal::access;
	template <class Archive>
	void serialize( Archive & ar)
	{
		ar(CEREAL_NVP(name));
	}

};

