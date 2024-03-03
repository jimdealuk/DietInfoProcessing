#include "../hpp/FoodInfoHandler.h"


namespace FoodInfoHandler {

	FoodInfoHandler::FoodInfoHandler() {
		foodInfo = std::make_unique<std::map<std::string, FoodInfoDbBase::FoodInfoDbBase*>>();
	}

	void FoodInfoHandler::CreateFoodInfoSource(std::string infoType) {

		std::map<std::string, FoodInfoDbBase::FoodInfoDbBase*>::iterator it = foodInfo->begin();

		while (it != foodInfo->end())
		{
			FoodInfoDbBase::FoodInfoDbBase* fiDb = new FoodInfoDbBase::FoodInfoDbBase();
			foodInfo->emplace(infoType, std::move(fiDb));
		}
	}

	bool FoodInfoHandler::AddFoodInfoToMap(std::string infoType, FoodInfoBase::FoodInfoBase infoToAdd) {

		std::map<std::string, FoodInfoDbBase::FoodInfoDbBase*>::iterator it = foodInfo->begin();

		it = foodInfo->find(infoType);
		if (it != foodInfo->end()) {
			it->second->addFoodInfo(infoToAdd.mDate, infoToAdd);
		}

		return true;
	}

}
