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
	DONE: PrintToFile function
	TODO: Handle different format in input files
    TODO: Exception Handling


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

	try {
		vehicles = VehicleRecords::importVehicles(VEHICLE_FILE);
		parms.retrieveParms(PARMS_FILE);
	} catch (invalid_argument &e) {
		cout << e.what() << endl;
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
