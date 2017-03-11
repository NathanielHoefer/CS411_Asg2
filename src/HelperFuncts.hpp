//==============================================================================
// Assignment 2 - Helper Functions
//==============================================================================
/*
    File: HelperFuncts.hpp
    Project: Assignment 2
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 3/11/2017

******************************************************************************/

#ifndef SRC_HELPERFUNCTS_HPP_
#define SRC_HELPERFUNCTS_HPP_

using namespace std;

vector<TripLeg> initializeTripLegs();
void printResults(VehicleTrip shortestTime, VehicleTrip longestTime, VehicleTrip leastFuelAdded,
				VehicleTrip mostFuelAdded, VehicleTrip leastFuelUsed, VehicleTrip mostFuelUsed,
				ofstream &output);
void printVehicleStats(VehicleTrip trip);
void printToFile(VehicleTrip trip, ofstream &output);

// Creates trip leg objects for the trip from Wichita to Monticello
//		Preconditions: None
//		Postconditions: None
//		Returns: a vector containing all of the instantiated trip legs in the
//			correct order
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

// Prints the results of the trip to the console and the ofstream provided.
//		Preconditions: The entered vehicle trips have already been run with the
//			stats calculated
//		Postconditions: The formatted results printed to the console and ofstream
void printResults(VehicleTrip shortestTime, VehicleTrip longestTime,
					VehicleTrip leastFuelAdded, VehicleTrip mostFuelAdded,
					VehicleTrip leastFuelUsed, VehicleTrip mostFuelUsed,
					ofstream &output)
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
	output << endl;
	printToFile(shortestTime, output);
	output << "  # Vehicle arriving first" << endl;

	cout << "========================================================" << endl;
	cout << "   2. Vehicle arriving last at Jefferson's Monticello: " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(longestTime);
	printToFile(longestTime, output);
	output << "  # Vehicle arriving last" << endl;

	cout << "========================================================" << endl;
	cout << "   3. Vehicle costing the least to reach Jefferson's    " << endl;
	cout << "        Monticello based on fuel added to tank:         " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(leastFuelAdded);
	printToFile(leastFuelAdded, output);
	output << "  # Vehicle costing least (fuel added)" << endl;

	cout << "========================================================" << endl;
	cout << "   4. Vehicle costing the most to reach Jefferson's     " << endl;
	cout << "        Monticello based on fuel added to tank:         " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(mostFuelAdded);
	printToFile(mostFuelAdded, output);
	output << "  # Vehicle costing most (fuel added)" << endl;

	cout << "========================================================" << endl;
	cout << "   5. Vehicle costing the least to reach Jefferson's    " << endl;
	cout << "         Monticello based on actual fuel used:          " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(leastFuelUsed);
	printToFile(leastFuelUsed, output);
	output << "  # Vehicle costing least (fuel used)" << endl;

	cout << "========================================================" << endl;
	cout << "   6. Vehicle costing the most to reach Jefferson's     " << endl;
	cout << "         Monticello based on actual fuel used:          " << endl;
	cout << "========================================================" << endl;
	printVehicleStats(mostFuelUsed);
	printToFile(mostFuelUsed, output);
	output << "  # Vehicle costing most (fuel used)" << endl;
}

// Prints the formatted vehicle stats from the trip entered to the console
//		Preconditions: The trip entered has already be run
//		Postconditions: Formatted stats are printed
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
	getline(results, temp, ',');
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

// Appends the vehicle stats from the trip entered to the stream entered
//		Preconditions: Trip entered has already been ran
//		Postcontitions: Trip printed in the following format:
//			Make|Model|EngineSize|EngineCylinders|TankSize|MpgCity|MpgHighway|Time(minutes)|Time(d.hh:mm)|
//			CostFueldAdded|CostFuelUsed|FuelAdded|FuelUsed|FuelRemaining|FuelStops
void printToFile(VehicleTrip trip, ofstream &output)
{
	stringstream results;
	results << trip;
	string temp;

	string make, model;
	int engineCylinders, cityMPG, highwayMPG, tripTime, gStationCnt;
	double engineSize, tankSize, currentFuel, fuelPurchased, fuelConsumed;

	// Parses the results from stream
	getline(results, temp, ',');
	make = temp;
	getline(results, temp, ',');
	model = temp;
	getline(results, temp, ',');
	engineSize = atof(temp.c_str());
	getline(results, temp, ',');
	engineCylinders = atoi(temp.c_str());
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

	// Calculations for formatted time
	int days, hours, minutes, remainingTime;
	remainingTime = tripTime;
	days = tripTime / (24 * 60);
	remainingTime = tripTime % (24 * 60);
	hours = remainingTime / 60;
	minutes = remainingTime % 60;

	double fuelAddedCost = fuelPurchased * trip.getParms().getFuelPrice();
	double fuelConsumedCost = fuelConsumed * trip.getParms().getFuelPrice();

	// Format:
	//	Make|Model|EngineSize|EngineCylinders|TankSize|MpgCity|MpgHighway|Time(minutes)|Time(d.hh:mm)|
	//	CostFueldAdded|CostFuelUsed|FuelAdded|FuelUsed|FuelRemaining|FuelStops
	output << left << setfill(' ') << setw(9) << make << "|" << setw(15) << model << "|";
	output << right << fixed << setfill('0') << setw(4) << setprecision(1) << engineSize << "|";
	output << engineCylinders << "|";
	output << setw(4) << tankSize << "|";
	output << setw(2) << cityMPG << "|" << setw(2) << highwayMPG << "|";
	output << setw(4) << tripTime << "|";
	output << days << "." << setfill('0') << right << setw(2) << hours << ":" << setw(2) << minutes << "|";
	output << setprecision(2) << setw(7) << fuelAddedCost << "|" << setw(7) << fuelConsumedCost << "|";
	output << setprecision(4) << setw(9) << fuelConsumed << "|" << setw(9) << fuelPurchased << "|";
	output << setw(9) << currentFuel << "|" << setw(2) << gStationCnt;
}

#endif /* SRC_HELPERFUNCTS_HPP_ */
