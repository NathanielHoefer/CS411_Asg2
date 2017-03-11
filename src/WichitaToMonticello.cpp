//==============================================================================
// Assignment 2 - WichitaToMonticello
//==============================================================================
/*
    File: WichitaToMonticello.cpp
    Project: Assignment 2
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 3/5/2017

    Simulates a trip from Wichita to Monticello with a number of vehicles to
    determine which vehicles take the least/most time, require the least/most
    fuel purchased, and require the least/most consumed. This program imports both
    the vehicles and the parameters from the string constants provided at the
    beginning of this file. The results are printed to the console as well as to
    the file specified by the string constant OUTPUT_FILE. Helper functions and
    Test drivers were moved to separate files in order to clean this file.

    Notes: Input values have not been fully checked for values ranging far beyond
    reasonable values since it was not explicitly mentioned in the rubric.

******************************************************************************/

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include "VehicleTrip.hpp"
#include "TripLeg.hpp"
#include "Vehicle.hpp"
#include "VehicleRecords.hpp"
#include "HelperFuncts.hpp"
#include "TestDrivers.hpp"

using namespace std;

static const string VEHICLE_FILE = "WichitaToMonticello-Vehicles.txt";
static const string PARMS_FILE = "WichitaToMonticello-Input.ini";
static const string OUTPUT_FILE = "WichitaToMonticello-Results.txt";

int main()
{
	cout << "========================================================" << endl;
	cout << "           Wichita to Monticello - Assignment 2         " << endl;
	cout << "========================================================" << endl;

//	tripTesting();	// Used for running test cases

	vector<Vehicle> vehicles;
	vector<TripLeg> tripLegs = initializeTripLegs();
	TripParameters parms;

	// Exits the program if vehicles or parameters are not properly imported
	try {
		vehicles = VehicleRecords::importVehicles(VEHICLE_FILE);
		parms.retrieveParms(PARMS_FILE);
	} catch (invalid_argument &e) {
		cout << e.what() << endl;
		cout << "ENDING PROGRAM";
		exit(1);
	} catch (exception &e) {
		cout << e.what() << endl;
		cout << "ENDING PROGRAM" << endl;
		exit(1);
	}

	// Run initial trip and initialize output stream
	VehicleTrip initialTrip(vehicles.at(0), parms);
	initialTrip.runTrip(tripLegs);
	ofstream outputStream(OUTPUT_FILE.c_str());
	outputStream << "Make|Model|EngineSize|EngineCylinders|TankSize|MpgCity|MpgHighway|Time(minutes)|Time(d.hh:mm)";
	outputStream << "|CostFueldAdded|CostFuelUsed|FuelAdded|FuelUsed|FuelRemaining|FuelStops" << endl;
	printToFile(initialTrip, outputStream);
	outputStream << endl;

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
		printToFile(trip, outputStream);
		outputStream << endl;

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
	printResults(shortestTime, longestTime, leastFuelAdded, mostFuelAdded,
			leastFuelUsed, mostFuelUsed, outputStream);
}
