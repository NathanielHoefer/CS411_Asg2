//==============================================================================
// Assignment 1 - Parameters Class
//==============================================================================
/*
    File: Parameters.hpp
    Project: Assignment 1
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 2/18/2017

******************************************************************************/

#ifndef PARAMETERS_HPP_
#define PARAMETERS_HPP_

// Constants for all default values
static const int 	CITY_MPH = 		25;
static const int 	HIGHWAY_MPH = 	70;
static const double FUEL_PRICE = 	2.19;	// Per gallon
static const double GAS_DISTANCE = 	80.0;	// Distance between gas stations
static const int 	REFUEL_TIME = 	20;		// in minutes
static const int 	RESTROOM_TIME = 10;		// in minutes
static const int 	NAP_TIME = 		15;		// in minutes
static const int 	AWAKE_TIME = 	8;		// in hours

class Parameters
{
private:
	int mCityMPH;
	int mHighwayMPH;
	double mFuelPrice;
	int mRefuelTimeMins;		// in minutes
	int mRestroomTimeMins;		// in minutes
	int mNapTimeMins;			// in minutes
	int mAwakeTimeMins;			// in minutes
	double mGasDistance;		// in miles

public:
	Parameters();
	Parameters(int cityMPH, int highwayMPH, double fuelPrice, int refuelTime,
			int restroomTimeMins, int napTimeMins, int awakeTimeHrs, double gasDistance);

	int 	getCityMph() const;
	int 	getHighwayMph() const;
	double 	getFuelPrice() const;
	int 	getRefuelTime() const;
	int 	getRestroomTime() const;
	int 	getNapTime() const;
	int 	getAwakeTime() const;
	double 	getGasDistance() const;

	void 	setCityMph(int cityMph);
	void 	setHighwayMph(int highwayMph);
	void 	setFuelPrice(double fuelPrice);
	void 	setRefuelTime(int refuelTime);
	void 	setRestroomTime(int restroomTime);
	void 	setNapTime(int napTime);
	void 	setAwakeTime(int awakeTime);
	void 	setGasDistance(double gastDistance);
};

#endif /* PARAMETERS_HPP_ */
