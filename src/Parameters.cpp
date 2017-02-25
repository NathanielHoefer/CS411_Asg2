//==============================================================================
// Assignment 1 - Parameters Class
//==============================================================================
/*
    File: Parameters.cpp
    Project: Assignment 1
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 2/18/2017

******************************************************************************/

#include "Parameters.hpp"

Parameters::Parameters()
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

Parameters::Parameters(int cityMPH, int highwayMPH, double fuelPrice, int refuelTime,
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

int 	Parameters::getCityMph() 		const { return mCityMPH; }
int 	Parameters::getHighwayMph() 	const { return mHighwayMPH; }
double 	Parameters::getFuelPrice() 		const { return mFuelPrice; }
int 	Parameters::getRefuelTime() 	const { return mRefuelTimeMins; }
int 	Parameters::getRestroomTime() 	const { return mRestroomTimeMins; }
int 	Parameters::getNapTime() 		const { return mNapTimeMins; }
int 	Parameters::getAwakeTime() 		const { return mAwakeTimeMins; }
double 	Parameters::getGasDistance() 	const { return mGasDistance; }

void 	Parameters::setCityMph(int cityMph) 			{ mCityMPH = cityMph; }
void 	Parameters::setHighwayMph(int highwayMph) 		{ mHighwayMPH = highwayMph; }
void 	Parameters::setFuelPrice(double fuelPrice) 		{ mFuelPrice = fuelPrice; }
void 	Parameters::setRefuelTime(int refuelTime) 		{ mRefuelTimeMins = refuelTime; }
void 	Parameters::setRestroomTime(int restroomTime) 	{ mRestroomTimeMins = restroomTime; }
void 	Parameters::setNapTime(int napTime) 			{ mNapTimeMins = napTime; }
void 	Parameters::setAwakeTime(int awakeTime) 		{ mAwakeTimeMins = awakeTime; }
void 	Parameters::setGasDistance(double gastDistance) { mGasDistance = gastDistance; }
