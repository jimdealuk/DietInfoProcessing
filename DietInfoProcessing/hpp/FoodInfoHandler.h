#pragma once

#include "FoodInfoDbBase.h"

#include <map>
#include <memory>

namespace FoodInfoHandler {

	class FoodInfoHandler {
	private:
		std::unique_ptr<std::map<std::string, FoodInfoDbBase::FoodInfoDbBase*>> foodInfo;


	public:
		FoodInfoHandler();

		void CreateFoodInfoSource(std::string infoType);

		bool AddFoodInfoToMap(std::string infoType, FoodInfoBase::FoodInfoBase foodInfo);
		

	};

}