//==============================================================================
// Assignment 2 - Trip Leg
//==============================================================================
/*
	File: TripLeg.hpp
    Project: Assignment 1
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 2/18/2017

******************************************************************************/

#ifndef TRIPLEG_HPP_
#define TRIPLEG_HPP_

class TripLeg
{
public:
	enum RoadType { HIGHWAY, CITY, DEFAULT };

private:
	double mDistance;
	RoadType mRoadType;

public:
	TripLeg();
	TripLeg(double distance, RoadType roadType);

	double getDistance();
	RoadType getRoadType();

};

#endif /* TRIPLEG_HPP_ */
