//==============================================================================
// Assignment 2 - WichitaToMonticello
//==============================================================================
/*
    File: WichitaToMonticello.cpp
    Project: Assignment 1
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 3/5/2017

    Simulates a trip from Wichita to Monticello with a number of vehicles to
    determine which vehicles take the least/most time, require the least/most
    fuel purchased, and require the least/most consumed.

    Notes: Input values have not been fully checked for values ranging far beyond
    reasonable values since it was not explicitly mentioned in the rubric.

	DONE: ImportVehicles function
	DONE: Update TripParameters Constructor
	DONE: TripParameters retrieveParms function
    DONE: Create a VehicleRecords Class
	TODO: PrintToFile function
    TODO: Exception Handling


******************************************************************************/

#include "VehicleTrip.hpp"
#include "TripLeg.hpp"
#include "Vehicle.hpp"
#include "VehicleRecords.hpp"
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;

// Helper function declarations
vector<TripLeg> initializeTripLegs();
void printResults(VehicleTrip shortestTime, VehicleTrip longestTime, VehicleTrip leastFuelAdded,
				VehicleTrip mostFuelAdded, VehicleTrip leastFuelUsed, VehicleTrip mostFuelUsed);
void printToFile(ofstream & outputFile);
void printVehicleStats(VehicleTrip trip);
void printExpectedStats(int testCase, double tankSize, int cityMPG, int highwayMPG, int tripTime, double fuelAddedCost,
		double fuelUsedCost, double fuelAdded, double fuelUsed, double fuelRemaining, int fuelStops);
void tripTesting();
void tripTesting2();


int main()
{
	cout << "========================================================" << endl;
	cout << "           Wichita to Monticello - Assignment 1         " << endl;
	cout << "========================================================" << endl;

//	tripTesting();	// Used for running test cases
//	tripTesting2();

	string vehFile = "WichitaToMonticello-Vehicles.txt";
	string parmsFile = "WichitaToMonticello-Input.ini";
	vector<Vehicle> vehicles = VehicleRecords::importVehicles(vehFile);
	vector<TripLeg> tripLegs = initializeTripLegs();
	TripParameters parms(parmsFile);

	VehicleTrip initialTrip(vehicles.at(0), parms);
	initialTrip.runTrip(tripLegs);

	// Initializes records
	VehicleTrip shortestTime = 	initialTrip;
	VehicleTrip longestTime = 	initialTrip;
	VehicleTrip leastFuelAdded = initialTrip;
	VehicleTrip mostFuelAdded = initialTrip;
	VehicleTrip leastFuelUsed = initialTrip;
	VehicleTrip mostFuelUsed = 	initialTrip;

	// Process each vehicle trip
	for (int i = 1; i < (int)vehicles.size(); i++) {
		VehicleTrip trip(vehicles.at(i), parms);
		trip.runTrip(tripLegs);

		// Updates records
		if (trip.getTripTime() < shortestTime.getTripTime())
			shortestTime = trip;
		if (trip.getTripTime() > longestTime.getTripTime())
			longestTime = trip;
		if (trip.getFuelPurchased() < leastFuelAdded.getFuelPurchased())
			leastFuelAdded = trip;
		if (trip.getFuelPurchased() > mostFuelAdded.getFuelPurchased())
			mostFuelAdded = trip;
		if (trip.getFuelConsumed() < leastFuelUsed.getFuelConsumed())
			leastFuelUsed = trip;
		if (trip.getFuelConsumed() > mostFuelUsed.getFuelConsumed())
			mostFuelUsed = trip;
	}

	// Print the formatted results
	printResults(shortestTime, longestTime, leastFuelAdded, mostFuelAdded, leastFuelUsed, mostFuelUsed);
}

// Creates trip leg objects
vector<TripLeg> initializeTripLegs()
{
	vector<TripLeg> tripLegs;

	tripLegs.push_back(TripLeg(3.3, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(23.2, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(0.05, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(0.2, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(56.2, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(50.3, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(6.8, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(53.5, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(21.3, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(229, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(2.8, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(74.7, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(47.3, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(69.3, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(0.2, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(24.3, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(21.2, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(79.2, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(208, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(181.3, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(86.6, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(106.7, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(8.0, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(45.6, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(0.1, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(0.5, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(22.7, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(0.6, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(1.7, 	TripLeg::CITY));

	return tripLegs;
}

// TODO
void printToFile(ofstream & outputFile)
{

}

// Prints the results of the trip
void printResults(VehicleTrip shortestTime, VehicleTrip longestTime,
					VehicleTrip leastFuelAdded, VehicleTrip mostFuelAdded,
					VehicleTrip leastFuelUsed, VehicleTrip mostFuelUsed)
{
	cout << "========================================================" << endl;
	cout << "                      Trip Results                      " << endl;
	cout << "========================================================" << endl;

	cout << setw(14) << "" << "Total miles driven = " << fixed << setprecision(2)
			<< shortestTime.getCityMiles() + shortestTime.getHighwayMiles()
			<< endl;
	cout << setw(10) << "" << fixed << setprecision(2) << left
			<< "City = " << setw(12) << shortestTime.getCityMiles();
	cout << fixed << setprecision(2) << "Highway = "
			<< shortestTime.getHighwayMiles() << endl << endl << endl;

	cout << "========================================================" << endl;
	cout << "   1. Vehicle ariving first at Jefferson's Monticello:  " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(shortestTime);

	cout << "========================================================" << endl;
	cout << "   2. Vehicle arriving last at Jefferson's Monticello: " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(longestTime);

	cout << "========================================================" << endl;
	cout << "   3. Vehicle costing the least to reach Jefferson's    " << endl;
	cout << "        Monticello based on fuel added to tank:         " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(leastFuelAdded);

	cout << "========================================================" << endl;
	cout << "   4. Vehicle costing the most to reach Jefferson's     " << endl;
	cout << "        Monticello based on fuel added to tank:         " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(mostFuelAdded);

	cout << "========================================================" << endl;
	cout << "   5. Vehicle costing the least to reach Jefferson's    " << endl;
	cout << "         Monticello based on actual fuel used:          " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(leastFuelUsed);

	cout << "========================================================" << endl;
	cout << "   6. Vehicle costing the most to reach Jefferson's     " << endl;
	cout << "         Monticello based on actual fuel used:          " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(mostFuelUsed);
}

// Prints the vehicle stats from the trip entered
void printVehicleStats(VehicleTrip trip)
{
	stringstream results;
	results << trip;
	string temp;

	string make, model;
	int cityMPG, highwayMPG, tripTime, gStationCnt;
	double tankSize, currentFuel, fuelPurchased, fuelConsumed;

	// Parses the results from stream
	getline(results, temp, ',');
	make = temp;
	getline(results, temp, ',');
	model = temp;
	getline(results, temp, ',');
	tankSize = atof(temp.c_str());
	getline(results, temp, ',');
	cityMPG = atoi(temp.c_str());
	getline(results, temp, ',');
	highwayMPG = atoi(temp.c_str());
	getline(results, temp, ',');
	currentFuel = atof(temp.c_str());
	getline(results, temp, ',');
	tripTime = atoi(temp.c_str());
	getline(results, temp, ',');
	fuelPurchased = atof(temp.c_str());
	getline(results, temp, ',');
	fuelConsumed = atof(temp.c_str());
	getline(results, temp, ',');
	gStationCnt = atoi(temp.c_str());

	// Calculations for centering title
	int titleLen = make.size() + model.size() + 1;
	int leftTitleSpace = (56 - titleLen) / 2;

	// Calculations for formatted time
	int days, hours, minutes, remainingTime;
	remainingTime = tripTime;
	days = tripTime / (24 * 60);
	remainingTime = tripTime % (24 * 60);
	hours = remainingTime / 60;
	minutes = remainingTime % 60;

	double fuelAddedCost = fuelPurchased * trip.getParms().getFuelPrice();
	double fuelConsumedCost = fuelConsumed * trip.getParms().getFuelPrice();

	// Formats output
	cout << setw(leftTitleSpace) << "";
	cout << make << " " << model		   << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << left << fixed << setprecision(2);
	cout << "Tank Size = " << setw(6) << tankSize;
	cout << "gal   City MPG = " << setw(5) << cityMPG;
	cout << "Highway MPG = " << highwayMPG << endl;;
	cout << "--------------------------------------------------------" << endl;
	cout << "Trip time(minutes) = " << setw(7) << tripTime;
	cout << "Trip time(d.hh:mm) = " << days << "." << setfill('0') << right
			<< setw(2) << hours << ":" << setw(2) << minutes << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << left << setfill(' ');
	cout << "Trip cost based on fuel added = $" << fuelAddedCost << endl;
	cout << "Trip cost based on fuel used  = $" << fuelConsumedCost << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Fuel added = " << setw(8) << setprecision(4) << fuelPurchased
			<< "gal    Fuel remaining = " << currentFuel << " gal" << endl;
	cout << "Fuel used  = " << setw(8) << fuelConsumed;
	cout << "gal    Fuel stops     = " << gStationCnt << endl << endl << endl;
}

void tripTesting2()
{
	vector<Vehicle> vehicles = VehicleRecords::importVehicles("WichitaToMonticello-Vehicles.txt");
	TripParameters parms("WichitaToMonticello-Input.ini");
	cout << parms.getCityMph() << " "
			<< parms.getHighwayMph() << " "
			<< parms.getFuelPrice() << " "
			<< parms.getGasDistance() << " "
			<< parms.getRefuelTime() << " "
			<< parms.getRestroomTime() << " "
			<< parms.getNapTime() << " "
			<< parms.getAwakeTime() << endl;
	exit(0);
}

// Function used for testing scenarios
void tripTesting()
{
	// Test Case 1 - Confirmed
	// Vehicle travels 1 trip leg containing 1 gas station, no refuel
	Vehicle v1("Actual:", "", 1, 1,
			2, 		// Tank size
			15, 	// cityMPG
			30);
	vector<TripLeg> l1;
	l1.push_back(TripLeg(20, TripLeg::CITY));			// Trip is 20 miles
	TripParameters p1(30, 60, 2.5, 20, 10, 15, 8, 15);		// Station every 15 miles
	VehicleTrip t1(v1, p1);
	t1.runTrip(l1);
	printExpectedStats(1, 2, 15, 30, 40, 0, 3.33, 0, 1.3333, .6666, 0);
	printVehicleStats(t1);

	// Test Case 2 - Confirmed
	// Vehicle travels 1 trip leg containing 1 gas station, need to refuel 1 time
	Vehicle v2("Actual:", "", 1, 1,
			1.75, 	// Tank size
			10, 	// cityMPG
			30);	// HighwayMPG
	vector<TripLeg> l2;
	l2.push_back(TripLeg(20, TripLeg::CITY));	// Trip is 20 miles
	TripParameters p2(
			30, 	// cityMPH
			60, 	// highwayMPH
			2.5, 	// Fuel Cost
			20, 	// Refuel Time
			10, 	// Restroom Time
			15, 	// Nap Time
			8, 		// Awake Time
			15);	// Station every 15 miles
	VehicleTrip t2(v2, p2);
	t2.runTrip(l2);
	printExpectedStats(
			2, 		// Test Case
			1.75, 	// Tank
			10, 	// CityMPG
			30, 	// HighwayMPG
			60, 	// Trip Time
			3.75, 	// Fuel Added Cost
			5, 		// Fuel Used Cost
			1.5, 	// Fuel Added
			2, 		// Fuel Used
			1.25, 	// Fuel Remaining
			1);		// Fuel Stops
	printVehicleStats(t2);

	// Test Case 3 - Confirmed
	// Vehicle travels 1 trip leg containing 3 gas stations, need to refuel 1 time
	Vehicle v3("Actual:", "", 1, 1,
			3.5, 	// Tank size
			10, 	// cityMPG
			30);	// HighwayMPG
	vector<TripLeg> l3;
	l3.push_back(TripLeg(50, TripLeg::CITY));	// Trip is 50 miles
	TripParameters p3(
			30, 	// cityMPH
			60, 	// highwayMPH
			2.5, 	// Fuel Cost
			20, 	// Refuel Time
			10, 	// Restroom Time
			15, 	// Nap Time
			8, 		// Awake Time
			15);	// Station every 15 miles
	VehicleTrip t3(v3, p3);
	t3.runTrip(l3);
	printExpectedStats(
			3, 		// Test Case
			3.5, 	// Tank Size
			10, 	// CityMPG
			30, 	// HighwayMPG
			120, 	// Trip Time
			7.5, 	// Fuel Added Cost
			12.5,	// Fuel Used Cost
			3,	 	// Fuel Added
			5, 		// Fuel Used
			1.5, 	// Fuel Remaining
			1);		// Fuel Stops
	printVehicleStats(t3);

	// Test Case 4 - Confirmed
	// Vehicle travels 1 trip leg containing 4 gas stations, need to refuel 2 times
	Vehicle v4("Actual:", "", 1, 1,
			3.6, 	// Tank size
			10, 	// cityMPG
			30);	// HighwayMPG
	vector<TripLeg> l4;
	l4.push_back(TripLeg(70, TripLeg::CITY));	// Trip is 70 miles
	TripParameters p4(
			30, 	// cityMPH
			60, 	// highwayMPH
			2.5, 	// Fuel Cost
			20, 	// Refuel Time
			10, 	// Restroom Time
			15, 	// Nap Time
			8, 		// Awake Time
			15);	// Station every 15 miles
	VehicleTrip t4(v4, p4);
	t4.runTrip(l4);
	printExpectedStats(
			4, 		// Test Case
			3.6, 	// Tank Size
			10, 	// CityMPG
			30, 	// HighwayMPG
			190, 	// Trip Time
			15, 	// Fuel Added Cost
			17.5,	// Fuel Used Cost
			6,	 	// Fuel Added
			7, 		// Fuel Used
			2.6, 	// Fuel Remaining
			2);		// Fuel Stops
	printVehicleStats(t4);

	// Test Case 5 - Confirmed
	// Vehicle travels city 2 trip legs containing 2 gas station each, need to refuel 2 times
	Vehicle v5("Actual:", "", 1, 1,
			4.5, 	// Tank size
			10, 	// cityMPG
			30);	// HighwayMPG
	vector<TripLeg> l5;
	l5.push_back(TripLeg(50, TripLeg::CITY));
	l5.push_back(TripLeg(50, TripLeg::CITY));	// Trip is 100 miles
	TripParameters p5(
			30, 	// cityMPH
			60, 	// highwayMPH
			2.5, 	// Fuel Cost
			20, 	// Refuel Time
			10, 	// Restroom Time
			15, 	// Nap Time
			3, 		// Awake Time
			22);	// Station every 22 miles
	VehicleTrip t5(v5, p5);
	t5.runTrip(l5);
	printExpectedStats(
			5, 		// Test Case
			4.5, 	// Tank Size
			10, 	// CityMPG
			30, 	// HighwayMPG
			265, 	// Trip Time
			22, 	// Fuel Added Cost
			25,		// Fuel Used Cost
			8.8,	// Fuel Added
			10, 	// Fuel Used
			3.3, 	// Fuel Remaining
			2);		// Fuel Stops
	printVehicleStats(t5);

	// Test Case 6 - Confirmed
	// Vehicle travels city 2 trip legs containing 2 gas station each, need to refuel 2 times
	// One Trip leg is City, the other Highway
	Vehicle v6("Actual:", "", 1, 1,
			2.4, 	// Tank size
			10, 	// cityMPG
			20);	// HighwayMPG
	vector<TripLeg> l6;
	l6.push_back(TripLeg(50, TripLeg::CITY));
	l6.push_back(TripLeg(50, TripLeg::HIGHWAY));	// Trip is 100 miles
	TripParameters p6(
			30, 	// cityMPH
			60, 	// highwayMPH
			2.5, 	// Fuel Cost
			20, 	// Refuel Time
			10, 	// Restroom Time
			15, 	// Nap Time
			2, 		// Awake Time
			22);	// Station every 22 miles
	VehicleTrip t6(v6, p6);
	t6.runTrip(l6);
	printExpectedStats(
			6, 		// Test Case
			2.4, 	// Tank Size
			10, 	// CityMPG
			20, 	// HighwayMPG
			235, 	// Trip Time
			14.5, 	// Fuel Added Cost
			18.75,		// Fuel Used Cost
			5.8,	// Fuel Added
			7.5, 	// Fuel Used
			.7, 	// Fuel Remaining
			3);		// Fuel Stops
	printVehicleStats(t6);

	// Test Case 7 - Confirmed
	// Vehicle travels city 2 trip legs containing 2 gas station each, need to refuel 2 times
	// One Trip leg is City, the other Highway
	Vehicle v7("Actual:", "", 1, 1,
			2.6, 	// Tank size
			10, 	// cityMPG
			20);	// HighwayMPG
	vector<TripLeg> l7;
	l7.push_back(TripLeg(50, TripLeg::CITY));
	l7.push_back(TripLeg(50, TripLeg::HIGHWAY));	// Trip is 100 miles
	TripParameters p7(
			30, 	// cityMPH
			60, 	// highwayMPH
			2.5, 	// Fuel Cost
			20, 	// Refuel Time
			10, 	// Restroom Time
			15, 	// Nap Time
			2, 		// Awake Time
			22);	// Station every 22 miles
	VehicleTrip t7(v7, p7);
	t7.runTrip(l7);
	printExpectedStats(
			7, 		// Test Case
			2.6, 	// Tank Size
			10, 	// CityMPG
			20, 	// HighwayMPG
			235, 	// Trip Time
			17.25, 	// Fuel Added Cost
			18.75,		// Fuel Used Cost
			6.9,	// Fuel Added
			7.5, 	// Fuel Used
			2, 	// Fuel Remaining
			3);		// Fuel Stops
	printVehicleStats(t7);

	// Test Case 8 - Confirmed
	// Vehicle travels multiple roadtypes and trip legs to test more realistic trip
	Vehicle v8("Actual:", "", 1, 1,
			1.12, 	// Tank size
			10, 	// cityMPG
			20);	// HighwayMPG
	vector<TripLeg> l8;
	l8.push_back(TripLeg(2.5, 	TripLeg::CITY));
	l8.push_back(TripLeg(3, 	TripLeg::CITY));
	l8.push_back(TripLeg(14.5, 	TripLeg::HIGHWAY));
	l8.push_back(TripLeg(20, 	TripLeg::HIGHWAY));
	l8.push_back(TripLeg(10, 	TripLeg::CITY));	// Trip is 50 miles
	TripParameters p8(
			30, 	// cityMPH
			60, 	// highwayMPH
			2.5, 	// Fuel Cost
			20, 	// Refuel Time
			10, 	// Restroom Time
			15, 	// Nap Time
			1, 		// Awake Time
			11);	// Station every 11 miles
	VehicleTrip t8(v8, p8);
	t8.runTrip(l8);
	printExpectedStats(
			8, 		// Test Case
			1.12, 	// Tank Size
			10, 	// CityMPG
			20, 	// HighwayMPG
			151, 	// Trip Time
			6.69, 	// Fuel Added Cost
			8.19,		// Fuel Used Cost
			2.675,	// Fuel Added
			3.275, 	// Fuel Used
			.52, 	// Fuel Remaining
			3);		// Fuel Stops
	printVehicleStats(t8);
}

void printExpectedStats(int testCase, double tankSize, int cityMPG, int highwayMPG, int tripTime, double fuelAddedCost,
		double fuelUsedCost, double fuelAdded, double fuelUsed, double fuelRemaining, int fuelStops)
{
	// Calculations for formatted time
	int days, hours, minutes, remainingTime;
	remainingTime = tripTime;
	days = tripTime / (24 * 60);
	remainingTime = tripTime % (24 * 60);
	hours = remainingTime / 60;
	minutes = remainingTime % 60;

	cout << "========================================================" << endl;
	cout << "                     Test Case: " << testCase 			<< endl;
	cout << "========================================================" << endl;
	cout << "                       Expected: " << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << left << fixed << setprecision(2);
	cout << "Tank Size = " << setw(6) << tankSize;
	cout << "gal   City MPG = " << setw(5) << cityMPG;
	cout << "Highway MPG = " << highwayMPG << endl;;
	cout << "--------------------------------------------------------" << endl;
	cout << "Trip time(minutes) = " << setw(7) << tripTime;
	cout << "Trip time(d.hh:mm) = " << days << "." << setfill('0') << right
			<< setw(2) << hours << ":" << setw(2) << minutes << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << left << setfill(' ');
	cout << "Trip cost based on fuel added = $" << fuelAddedCost << endl;
	cout << "Trip cost based on fuel used  = $" << fuelUsedCost << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Fuel added = " << setw(8) << setprecision(4) << fuelAdded
			<< "gal    Fuel remaining = " << fuelRemaining << " gal" << endl;
	cout << "Fuel used  = " << setw(8) << fuelUsed;
	cout << "gal    Fuel stops     = " << fuelStops << endl;
	cout << "========================================================" << endl;
}
