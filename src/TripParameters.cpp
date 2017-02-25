//==============================================================================
// Assignment 1 - TripParameters Class
//==============================================================================
/*
    File: TripParameters.cpp
    Project: Assignment 1
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 2/18/2017

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
bool TripParameters::retrieveParms(std::string file)
{
	return false;
}
