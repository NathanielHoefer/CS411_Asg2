//==============================================================================
// Assignment 2 - TripParameters Class
//==============================================================================
/*
    File: TripParameters.cpp
    Project: Assignment 1
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 3/5/2017

******************************************************************************/

#include "TripParameters.hpp"

TripParameters::TripParameters()
{
	mCityMPH = 			CITY_MPH;
	mHighwayMPH = 		HIGHWAY_MPH;
	mFuelPrice = 		FUEL_PRICE;
	mRefuelTimeMins = 	REFUEL_TIME;
	mRestroomTimeMins = RESTROOM_TIME;
	mNapTimeMins = 		NAP_TIME;
	mAwakeTimeMins = 	AWAKE_TIME * 60;
	mGasDistance = 		GAS_DISTANCE;
}

TripParameters::TripParameters(int cityMPH, int highwayMPH, double fuelPrice, int refuelTime,
		int restroomTimeMins, int napTimeMins, int awakeTimeHrs, double gasDistance)
{
	mCityMPH = 			cityMPH;
	mHighwayMPH = 		highwayMPH;
	mFuelPrice = 		fuelPrice;
	mRefuelTimeMins = 	refuelTime;
	mRestroomTimeMins = restroomTimeMins;
	mNapTimeMins = 		napTimeMins;
	mAwakeTimeMins = 	awakeTimeHrs * 60;
	mGasDistance = 		gasDistance;
}

// TODO
TripParameters::TripParameters(std::string file)
{
	mCityMPH = 			CITY_MPH;
	mHighwayMPH = 		HIGHWAY_MPH;
	mFuelPrice = 		FUEL_PRICE;
	mRefuelTimeMins = 	REFUEL_TIME;
	mRestroomTimeMins = RESTROOM_TIME;
	mNapTimeMins = 		NAP_TIME;
	mAwakeTimeMins = 	AWAKE_TIME * 60;
	mGasDistance = 		GAS_DISTANCE;
	retrieveParms(file);
}

int 	TripParameters::getCityMph() 		const { return mCityMPH; }
int 	TripParameters::getHighwayMph() 	const { return mHighwayMPH; }
double 	TripParameters::getFuelPrice() 		const { return mFuelPrice; }
int 	TripParameters::getRefuelTime() 	const { return mRefuelTimeMins; }
int 	TripParameters::getRestroomTime() 	const { return mRestroomTimeMins; }
int 	TripParameters::getNapTime() 		const { return mNapTimeMins; }
int 	TripParameters::getAwakeTime() 		const { return mAwakeTimeMins; }
double 	TripParameters::getGasDistance() 	const { return mGasDistance; }

void 	TripParameters::setCityMph(int cityMph) 			{ mCityMPH = cityMph; }
void 	TripParameters::setHighwayMph(int highwayMph) 		{ mHighwayMPH = highwayMph; }
void 	TripParameters::setFuelPrice(double fuelPrice) 		{ mFuelPrice = fuelPrice; }
void 	TripParameters::setRefuelTime(int refuelTime) 		{ mRefuelTimeMins = refuelTime; }
void 	TripParameters::setRestroomTime(int restroomTime) 	{ mRestroomTimeMins = restroomTime; }
void 	TripParameters::setNapTime(int napTime) 			{ mNapTimeMins = napTime; }
void 	TripParameters::setAwakeTime(int awakeTime) 		{ mAwakeTimeMins = awakeTime; }
void 	TripParameters::setGasDistance(double gastDistance) { mGasDistance = gastDistance; }

// TODO
void TripParameters::retrieveParms(std::string file)
{
	std::ifstream stream;
	stream.open(file.c_str(), std::ifstream::in);
	std::string line = "";
	double value = 0;
	while (!stream.eof()) {
		std::getline(stream, line);

		// Trim input line
		line.erase(0, line.find_first_not_of(" \t\r\n"));

		// Check to see if it is a comment line
		if (line[0] != '#' && !line.empty()) {
			int index = line.find('=');
			value = std::atof(line.substr(index + 1, line.length() - index).c_str());
			line = line.substr(0, index);

			if (line == CITY_MPH_LABEL) {
				mCityMPH = (int) value;
			} else if (line == HIGHWAY_MPH_LABEL) {
				mHighwayMPH = (int) value;
			} else if (line == FUEL_PRICE_LABEL) {
				mFuelPrice = value;
			} else if (line == GAS_DISTANCE_LABEL) {
				mGasDistance = value;
			} else if (line == AWAKE_TIME_LABEL) {
				mAwakeTimeMins = (int) value * 60;
			} else if (line == REFUEL_TIME_LABEL) {
				mRefuelTimeMins = (int) value;
			} else if (line == RESTROOM_TIME_LABEL) {
				mRestroomTimeMins = (int) value;
			} else if (line == NAP_TIME_LABEL) {
				mNapTimeMins = (int) value;
			}
		}
	}
}
