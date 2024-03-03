#pragma once

#include "../XML/tinyxml2.h"

#include <ctime>
#include <string>


namespace FoodInfoBase {

	class FoodInfoBase {
	public:
		time_t mDate = 0;
		int mSnack = 0;
		int mBreakfast = 0;
		int mLunch = 0;
		int mDinner = 0;

		FoodInfoBase();
		FoodInfoBase(const FoodInfoBase& foodBase);
		~FoodInfoBase() = default;

		bool operator==(FoodInfoBase& foodBase);

		virtual void SetFoodInfoFromXMLString(std::string file);
		virtual void SetFoodInfoFromXML(tinyxml2::XMLElement* xml);

		virtual std::string GetFoodInfoXMLElement();

	};
}
