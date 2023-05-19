#pragma once
//#include <string>
//#include <map>
//#include <memory>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/archives/json.hpp>
#include <fstream>
#include <iostream>


class GameObject
{
public:
	std::string name;

	GameObject(std::string name);
	std::string getChoiceDetailString();
	std::map<std::string, std::string>& getSlotDetailMap();
	GameObject();
	void virtual save();

protected:

	friend class cereal::access;
	std::string choiceDetailString;
	std::map<std::string, std::string> slotDetailMap;

	void virtual generateChoiceDetailString();
	void virtual generateSlotDetailMap();

	template <class Archive>
	void serialize( Archive & ar)
	{
		ar(CEREAL_NVP(name));
	}
	//template <class Archive>
	//static void load_and_construct(Archive& ar, cereal::construct<GameObject>& construct)
	//{
	//	std::string name;
	//	ar(name);
	//	construct(name);
	//};
};

