#include "../hpp/FoodInfoDbBase.h"
#include "../XML/tinyxml2.h"

#include <algorithm>

#include <iterator>

#include <iostream>     // std::cout
#include <sstream> 

#include <iomanip>


using namespace tinyxml2;


namespace FoodInfoDbBase {

	FoodInfoDbBase::FoodInfoDbBase() {
		foodInfo = std::make_unique<std::map<time_t,FoodInfoBase::FoodInfoBase, std::greater<time_t>>>();

	}

	void FoodInfoDbBase::processFoodInfoSource(std::string source) {
		XMLDocument doc;
		XMLError err = doc.LoadFile(source.c_str());

		if (err == 0) {
			tinyxml2::XMLElement* parent = doc.FirstChildElement("Info");

			if (parent) {
				tinyxml2::XMLElement* row = parent->FirstChildElement("DailyInfo");
				while (row != NULL) {

					FoodInfoBase::FoodInfoBase fb;
					fb.SetFoodInfoFromXML(row);

					foodInfo->emplace(fb.mDate, fb);

					row = row->NextSiblingElement(); // next element

				} // end while col
			}
        } // end while row

		int n = 0;
	}

	void FoodInfoDbBase::processFoodInfoDb(std::string db) {

		std::map<time_t, FoodInfoBase::FoodInfoBase, std::greater<time_t>>::iterator it = foodInfo->begin();

		XMLDocument xmlDoc;

		XMLNode* pRoot = xmlDoc.NewElement("Info");
		xmlDoc.InsertFirstChild(pRoot);


		while (it != foodInfo->end())
		{

			FoodInfoBase::FoodInfoBase fb = it->second;

			std::string el = fb.GetFoodInfoXMLElement();

			XMLElement* dailyInfo = xmlDoc.NewElement("DailyInfo");

			XMLElement* snack = xmlDoc.NewElement("snack");
			snack->SetText(fb.mSnack);
			dailyInfo->InsertFirstChild(snack);

			XMLElement* breakfast = xmlDoc.NewElement("breakfast");
			breakfast->SetText(fb.mBreakfast);
			dailyInfo->InsertEndChild(breakfast);

			XMLElement* lunch = xmlDoc.NewElement("lunch");
			lunch->SetText(fb.mLunch);
			dailyInfo->InsertEndChild(lunch);

			XMLElement* dinner = xmlDoc.NewElement("dinner");
			dinner->SetText(fb.mDinner);
			dailyInfo->InsertEndChild(dinner);

			XMLElement* date = xmlDoc.NewElement("date");

			time_t rawtime(fb.mDate);
			struct tm timeinfo;
			localtime_s(&timeinfo, &rawtime);

			std::ostringstream oss;
			oss << std::put_time(&timeinfo, "%d-%m-%Y %H-%M-%S");
			auto strTime = oss.str();

			date->SetText(strTime.c_str());
			dailyInfo->InsertEndChild(date);

			XMLPrinter printer;
			dailyInfo->Accept(&printer);
			std::stringstream ss;
			ss << printer.CStr();
			std::string str = ss.str();

			pRoot->InsertEndChild(dailyInfo);

			it++;
		}
		xmlDoc.SaveFile(db.c_str());
	}

	void FoodInfoDbBase::getFoodInfoDb(std::map<time_t, FoodInfoBase::FoodInfoBase>& data) {
		std::map<time_t, FoodInfoBase::FoodInfoBase, std::greater<time_t>>::iterator it = foodInfo->begin();

		while (it != foodInfo->end())
		{
			data.insert(std::pair<time_t, FoodInfoBase::FoodInfoBase>(it->first, it->second));
		}
	}

	bool FoodInfoDbBase::addFoodInfo(const time_t date, int snack, int breakfast, int lunch, int dinner) {
		FoodInfoBase::FoodInfoBase fb;
		fb.mSnack = snack;
		fb.mBreakfast = breakfast;
		fb.mLunch = lunch;
		fb.mDinner = dinner;

		return this->addFoodInfo(date, fb);

	}

	bool FoodInfoDbBase::addFoodInfo(const time_t date, FoodInfoBase::FoodInfoBase food) {

		std::pair<std::map<time_t, FoodInfoBase::FoodInfoBase, std::greater<time_t>>::iterator, bool> result = foodInfo->insert(std::pair<time_t, FoodInfoBase::FoodInfoBase>(date,food));

		return result.second;
	}



}
