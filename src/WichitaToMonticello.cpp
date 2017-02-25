//==============================================================================
// Assignment 1 - WichitaToMonticello
//==============================================================================
/*
    File: WichitaToMonticello.cpp
    Project: Assignment 1
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 2/18/2017

    Simulates a trip from Wichita to Monticello with a number of vehicles to
    determine which vehicles take the least/most time, require the least/most
    fuel purchased, and require the least/most consumed.

    Notes: Input values have not been fully checked for values ranging far beyond
    reasonable values since it was not explicitly mentioned in the rubric.

******************************************************************************/

#include "VehicleTrip.hpp"
#include "TripLeg.hpp"
#include "Vehicle.hpp"
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;

// Helper function declarations
vector<Vehicle> initializeVehicles();
vector<TripLeg> initializeTripLegs();
Parameters initializeParms();
double requestInput(double defaultVal);
void printResults(VehicleTrip shortestTime, VehicleTrip longestTime, VehicleTrip leastFuelAdded,
				VehicleTrip mostFuelAdded, VehicleTrip leastFuelUsed, VehicleTrip mostFuelUsed);
void printVehicleStats(VehicleTrip trip);
void printExpectedStats(int testCase, double tankSize, int cityMPG, int highwayMPG, int tripTime, double fuelAddedCost,
		double fuelUsedCost, double fuelAdded, double fuelUsed, double fuelRemaining, int fuelStops);
void tripTesting();


int main()
{
	cout << "========================================================" << endl;
	cout << "           Wichita to Monticello - Assignment 1         " << endl;
	cout << "========================================================" << endl;

//	tripTesting();	// Used for running test cases

	vector<Vehicle> vehicles = initializeVehicles();
	vector<TripLeg> tripLegs = initializeTripLegs();
	Parameters parms = initializeParms();

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

// Creates the vehicle objects
vector<Vehicle> initializeVehicles()
{
	vector<Vehicle> vehicles;

	vehicles.push_back(Vehicle("Chevrolet", "Spark", 			1.2, 4, 10.5, 	28, 36));
	vehicles.push_back(Vehicle("Chevrolet", "Cruze", 			1.8, 4, 12.5, 	22, 35));
	vehicles.push_back(Vehicle("Chevrolet", "Sonic", 			1.8, 4, 12, 	25, 35));
	vehicles.push_back(Vehicle("Chevrolet", "Camaro",			3.6, 6, 13, 	19, 28));
	vehicles.push_back(Vehicle("Chevrolet", "Suburban C1500", 	5.3, 8, 33, 	13, 18));
	vehicles.push_back(Vehicle("Chevrolet", "Suburban C2500",	6.0, 8, 36, 	10, 15));
	vehicles.push_back(Vehicle("Chrysler", "Town & Country",	3.6, 6, 12.5, 	22, 29));
	vehicles.push_back(Vehicle("Chrysler","300",				5.7, 8, 13.5, 	18, 28));
	vehicles.push_back(Vehicle("Dodge", "Grand Caravan",		3.6, 4, 12.5, 	23, 29));
	vehicles.push_back(Vehicle("Dodge", "Challenger",			5.7, 4, 13, 	16, 25));
	vehicles.push_back(Vehicle("Dodge", "Charger",				5.7, 4, 13, 	17, 26));
	vehicles.push_back(Vehicle("Ford", "Fiesta",				1.6, 4, 9.5, 	29, 39));
	vehicles.push_back(Vehicle("Ford", "Focus",					2.0, 4, 11.5, 	27, 38));
	vehicles.push_back(Vehicle("Ford", "Fusion",				2.0, 4, 12.5, 	22, 33));
	vehicles.push_back(Vehicle("Ford", "Taurus",				3.5, 4, 13, 	19, 29));
	vehicles.push_back(Vehicle("Ford", "Mustang",				5.0, 4, 12, 	18, 25));
	vehicles.push_back(Vehicle("Ford", "E150 Wagon",			5.4, 4, 33.5, 	14, 17));
	vehicles.push_back(Vehicle("Ford", "E350 Wagon",			5.4, 4, 36.5, 	9, 	16));
	vehicles.push_back(Vehicle("Ford", "Expedition 4WD",		5.4, 4, 19, 	13, 19));
	vehicles.push_back(Vehicle("Ford", "F150 Pickup 2WD",		6.2, 4, 25.5, 	15, 20));
	vehicles.push_back(Vehicle("Ford", "F150 Pickup 4WD",		6.2, 4, 23, 	14, 19));
	vehicles.push_back(Vehicle("Honda", "Civic",				1.8, 4, 12, 	28, 39));
	vehicles.push_back(Vehicle("Honda", "Accord",				3.5, 4, 12.5, 	21, 34));
	vehicles.push_back(Vehicle("Hyundai", "Accent",				1.6, 4, 10.5, 	28, 37));
	vehicles.push_back(Vehicle("Hyundai", "Elantra",			1.8, 4, 13, 	28, 38));
	vehicles.push_back(Vehicle("Hyundai", "Sonata",				2.4, 4, 13.5, 	24, 35));
	vehicles.push_back(Vehicle("Mazda", "MAZDA3",				2.0, 4, 11, 	24, 33));
	vehicles.push_back(Vehicle("Mazda", "MAZDA5",				2.5, 4, 11.5, 	22, 28));
	vehicles.push_back(Vehicle("Mazda", "MAZDA6",				3.7, 4, 12, 	18, 27));
	vehicles.push_back(Vehicle("Toyota", "Corolla",				1.8, 4, 12.5, 	26, 34));
	vehicles.push_back(Vehicle("Toyota", "Sienna",				2.7, 4, 13, 	19, 24));
	vehicles.push_back(Vehicle("Toyota", "Camry",				3.5, 4, 13.5, 	21, 31));
	vehicles.push_back(Vehicle("Toyota", "4Runner 4WD",			4.0, 4, 15, 	17, 21));

	return vehicles;
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

Parameters initializeParms()
{
	int cityMPH, highwayMPH, refuelTime, restroomTime, napTime, awakeTime;
	double fuelPrice, gasDistance;
	string input = "";
	bool isFinished, isApproved;
	isFinished = isApproved = false;

	while (!isFinished) {
		isFinished = isApproved = false;

		cout << "Enter the following parameters: " << endl;
		cout << " - Average speed in the city (MPH) [25]: ";
		cityMPH = (int)requestInput(CITY_MPH);
		cout << " - Average speed on the highway (MPH) [70]: ";
		highwayMPH = (int)requestInput(HIGHWAY_MPH);
		cout << " - Average fuel price per gallon [2.19]: ";
		fuelPrice = requestInput(FUEL_PRICE);
		cout << " - Distance between gas stations (miles) [80.0]: ";
		gasDistance = requestInput(GAS_DISTANCE);
		cout << " - Time required to refuel (minutes) [20]: ";
		refuelTime = (int)requestInput(REFUEL_TIME);
		cout << " - Time required to use the restroom (minutes) [10]: ";
		restroomTime = (int)requestInput(RESTROOM_TIME);
		cout << " - Time required to take a nap (minutes) [15]: ";
		napTime = (int)requestInput(NAP_TIME);
		cout << " - Time before requiring sleep (hours) [8]: ";
		awakeTime = round(requestInput(AWAKE_TIME));

		cout << "\n--------------------------------------------------------"
				<< endl << endl;

		// Verifies input with user
		while (!isApproved) {
			cout << left << setw(13) << "City MPH:" << right
					<< setfill('0') << setw(2) << cityMPH
					<< setfill(' ') << setw(3) << "";
			cout << left << setw(21) << "Refuel Time (min):" << right
					<< setfill('0') << setw(2) << refuelTime
					<< setfill(' ') << setw(3) << "";
			cout << left << setw(18) << "Nap Time (min):" << right
					<< setfill('0') << setw(2) << napTime
					<< setfill(' ') << endl;
			cout << left << setw(13) << "Highway MPH:" << right
					<< setfill('0') << setw(2) << highwayMPH
					<< setfill(' ') << setw(3) << "";
			cout << left << setw(21) << "Restroom Time (min):" << right
					<< setfill('0') << setw(2) << restroomTime
					<< setfill(' ') << setw(3) << "";
			cout << left << setw(18) << "Awake Time (hr):" << right
					<< setfill(' ') << setw(2) << awakeTime
					<< setfill(' ') << endl;
			cout << left << setw(30) << "Gas Station Distance (miles): "
					<< fixed << setprecision(1) << setw(9) << gasDistance
					<< "Fuel Price: $" << setprecision(2) << fuelPrice << endl;
			cout << " - Are the entered parameters correct? (Y/N)" << endl;

			getline(cin, input);

			if (input == "Y" || input == "y") {
				isFinished = true;
				isApproved = true;
			} else if (input == "N" || input == "n") {
				cout << "--------------------------------------------------------"
						<< endl << endl;
				isApproved = true;
			} else {
				cout << "--------------------------------------------------------"
						<< endl << endl;
			}
		}
	}

	Parameters parms(cityMPH, highwayMPH, fuelPrice, refuelTime,
					restroomTime, napTime, awakeTime, gasDistance);
	cout << "--------------------------------------------------------" << endl;
	cout << endl;
	return parms;
}

// Checks if input is valid
double requestInput(double defaultVal)
{
	double value = defaultVal;
	string input = "";

	while (true) {
		getline(cin, input);

		if (input.empty() || input == "\r") {
			return defaultVal;
		}

		// Converts string to value
		stringstream stream(input);
		if (stream >> value)
			return value;
		cout << "Invalid value, please try again" << endl;
	}
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
	Parameters p1(30, 60, 2.5, 20, 10, 15, 8, 15);		// Station every 15 miles
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
	Parameters p2(
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
	Parameters p3(
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
	Parameters p4(
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
	Parameters p5(
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
	Parameters p6(
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
	Parameters p7(
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
	Parameters p8(
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
