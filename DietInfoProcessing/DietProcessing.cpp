// DietProcessing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "hpp/FoodInfoBase.h"
#include "hpp/FoodInfoDbBase.h"
#include "XML/tinyxml2.h"

int main()
{

    const std::string info = { "C:\\Users\\james\\Documents\\DietProcessing\\DietProcessing\\DietProcessing\\Data\\daily.xml" };
    FoodInfoDbBase::FoodInfoDbBase fdb;
    fdb.processFoodInfoSource(info);

    const std::string infoOut = { "C:\\Users\\james\\Documents\\DietProcessing\\DietProcessing\\DietProcessing\\Data\\daily_out.xml" };
    fdb.processFoodInfoDb(infoOut);

    std::cout << "Hello World!\n";
}

