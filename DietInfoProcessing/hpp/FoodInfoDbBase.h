#pragma once

#include "../XML/tinyxml2.h"
#include "FoodInfoBase.h"

#include <map>
#include <memory>

namespace FoodInfoDbBase {

	class FoodInfoDbBase {
	private:
		std::unique_ptr<std::map<time_t, FoodInfoBase::FoodInfoBase, std::greater<time_t>>> foodInfo;

	public:

		FoodInfoDbBase();
		FoodInfoDbBase(FoodInfoDbBase& fBase) = delete;
		~FoodInfoDbBase() = default;

		void processFoodInfoSource(std::string source);
		void processFoodInfoDb(std::string db);

		bool addFoodInfo(const time_t date = 0, int snack = 0, int breakfast = 0, int lunch = 0, int dinner = 0);
		bool addFoodInfo(const time_t date, FoodInfoBase::FoodInfoBase food);

		void getFoodInfoDb(std::map<time_t, FoodInfoBase::FoodInfoBase>& data);

	};
}

