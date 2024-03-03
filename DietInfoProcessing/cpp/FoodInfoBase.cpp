#include "../hpp/FoodInfoBase.h"

#include "../XML/tinyxml2.h"

#include <fstream>
#include <sstream>
#include <iomanip>

#include <chrono>

// https://shilohjames.wordpress.com/2014/04/27/tinyxml2-tutorial/

using namespace tinyxml2;


namespace FoodInfoBase {

	FoodInfoBase::FoodInfoBase() {

	}

	FoodInfoBase::FoodInfoBase(const FoodInfoBase& foodBase) {
		mDate = foodBase.mDate;
		mSnack = foodBase.mSnack;
		mBreakfast = foodBase.mBreakfast;
		mLunch = foodBase.mLunch;
		mDinner = foodBase.mDinner;
	}


	void FoodInfoBase::SetFoodInfoFromXMLString(std::string file) {

		//const std::string file = { "C:\\Users\\james\\Documents\\DietProcessing\\DietProcessing\\DietProcessing\\Data\\basicInfo.xml" };

		XMLDocument doc;

		XMLError err = doc.LoadFile(file.c_str());

		const  XMLElement* root = doc.FirstChildElement("Info");
		if (root) {

			const  XMLElement* dailyInfo = root->FirstChildElement("DailyInfo");
			if (dailyInfo) {
				const  XMLElement* snack = dailyInfo->FirstChildElement("snack");
				if (snack) {
					std::string i = snack->GetText();
					if (i.length() > 0) {
						try {
							mSnack = std::stoi(i);
						}
						catch (...) {
							// do nothing
						}
					}
				}
				const  XMLElement* breakfast = dailyInfo->FirstChildElement("breakfast");
				if (breakfast) {
					std::string i = breakfast->GetText();
					if (i.length() > 0) {
						try {
							mBreakfast = std::stoi(i);
						}
						catch (...) {
							// do nothing
						}
					}
				}
				const  XMLElement* lunch = dailyInfo->FirstChildElement("lunch");
				if (lunch) {
					std::string i = lunch->GetText();
					if (i.length() > 0) {
						try {
							mLunch = std::stoi(i);
						}
						catch (...) {
							// do nothing
						}
					}
				}
				const  XMLElement* dinner = dailyInfo->FirstChildElement("dinner");
				if (dinner) {
					std::string i = dinner->GetText();
					if (i.length() > 0) {
						try {
							mDinner = std::stoi(i);
						}
						catch (...) {
							// do nothing
						}
					}
				}

				const  XMLElement* date = dailyInfo->FirstChildElement("date");
				if (date) {
					std::string i = date->GetText();
					if (i.length() > 0) {
						try {
							struct tm tm;
							std::istringstream iss(i + " 00:00:00");
							iss >> std::get_time(&tm, "%d/%b/%Y %H:%M:%S");

							// https://stackoverflow.com/questions/40781934/c-current-time-two-digits
							// year starts at 1900
							// https://en.cppreference.com/w/cpp/io/manip/get_time
							mDate = mktime(&tm);


							struct tm newtime;
							localtime_s(&newtime, &mDate);

							int y = 0; // debug stop point

						}
						catch (...) {
							// do nothing
						}
					}
				}
			}

		}
	}
	

	std::string FoodInfoBase::GetFoodInfoXMLElement() {
		tinyxml2::XMLDocument* xmlDoc = new XMLDocument();

//		XMLElement* pRoot = xmlDoc->NewElement("Info");
//		xmlDoc->InsertFirstChild(pRoot);
//		XMLElement* dailyInfo = xmlDoc->NewElement("DailyInfo");
//		xmlDoc->InsertFirstChild(dailyInfo);

		XMLElement* snack = xmlDoc->NewElement("snack");
		snack->SetText(mSnack);
		xmlDoc->InsertEndChild(snack);

		XMLElement* breakfast = xmlDoc->NewElement("breakfast");
		breakfast->SetText(mBreakfast);
		xmlDoc->InsertEndChild(breakfast);

		XMLElement* lunch = xmlDoc->NewElement("lunch");
		lunch->SetText(mLunch);
		xmlDoc->InsertEndChild(lunch);

		XMLElement* dinner = xmlDoc->NewElement("dinner");
		dinner->SetText(mDinner);
		xmlDoc->InsertEndChild(dinner);

		XMLElement* date = xmlDoc->NewElement("date");
		date->SetText(mDate);
		xmlDoc->InsertEndChild(date);

//		const std::string infoOut = { "C:\\Users\\james\\Documents\\DietProcessing\\DietProcessing\\DietProcessing\\Data\\daily_out_1.xml" };
//		xmlDoc->SaveFile(infoOut.c_str());

		XMLPrinter printer1;
		xmlDoc->Accept(&printer1);
		std::stringstream ss1;
		ss1 << printer1.CStr();
		return ss1.str();
	}

	void FoodInfoBase::SetFoodInfoFromXML(tinyxml2::XMLElement* xml) {

		const  XMLElement* snack = xml->FirstChildElement("snack");
		if (snack) {
			std::string i = snack->GetText();
			if (i.length() > 0) {
				try {
					mSnack = std::stoi(i);
				}
				catch (...) {
					// do nothing
				}
			}
		}
		const  XMLElement* breakfast = xml->FirstChildElement("breakfast");
		if (breakfast) {
			std::string i = breakfast->GetText();
			if (i.length() > 0) {
				try {
					mBreakfast = std::stoi(i);
				}
				catch (...) {
					// do nothing
				}
			}
		}
		const  XMLElement* lunch = xml->FirstChildElement("lunch");
		if (lunch) {
			std::string i = lunch->GetText();
			if (i.length() > 0) {
				try {
					mLunch = std::stoi(i);
				}
				catch (...) {
					// do nothing
				}
			}
		}
		const  XMLElement* dinner = xml->FirstChildElement("dinner");
		if (dinner) {
			std::string i = dinner->GetText();
			if (i.length() > 0) {
				try {
					mDinner = std::stoi(i);
				}
				catch (...) {
					// do nothing
				}
			}
		}

		const  XMLElement* date = xml->FirstChildElement("date");
		if (date) {
			std::string i = date->GetText();
			if (i.length() > 0) {
				try {

					struct tm tm;
					std::istringstream iss(i + " 00:00:00");
					iss >> std::get_time(&tm, "%d-%b-%Y %H:%M:%S");

					// https://stackoverflow.com/questions/40781934/c-current-time-two-digits
					// year starts at 1900
					// https://en.cppreference.com/w/cpp/io/manip/get_time
					mDate = mktime(&tm);


					struct tm newtime;
					localtime_s(&newtime, &mDate);

					//mDate = std::stoi(i);

					//struct tm newtime;
					//localtime_s(&newtime, &mDate);

					int y = 0; // debug stop point
				}
				catch (...) {
					// do nothing
				}
			}
		}
	}

	bool FoodInfoBase::operator == (FoodInfoBase & foodBase){
		bool ret = true;
		if ((this->mSnack == foodBase.mSnack) &&
			(this->mBreakfast == foodBase.mBreakfast) &&
			(this->mLunch == foodBase.mLunch) &&
			(this->mDinner == foodBase.mDinner) &&
			(this->mDate == foodBase.mDate)) {
			ret = true;
		}

		return ret;
	}


};