//==============================================================================
// Assignment 2 - Vehicle Records Class
//==============================================================================
/*
    File: VehicleRecords.hpp
    Project: Assignment 2
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 3/5/2017

******************************************************************************/

#include "VehicleRecords.hpp"

namespace
{
	// Parses the input string based on the delimiter given and the element requested.
	//	Preconditions: Elements begin with zero and if exceeds the number of elements within
	//		the string, it will loop around.
	//	Postconditions: None
	//	Returns: String of the parsed element
	std::string parseLine(const std::string str, const int element, const char delimeter)
	{
		int index, len;
		index = len = 0;
		len = str.find(delimeter);
		for (int i = 0; i < element; i++) {
			index += len + 1;
			len = str.find(delimeter, index) - index;
		}
		return str.substr(index, len);
	}
}

std::vector<Vehicle> VehicleRecords::importVehicles(std::string file)
{
	std::ifstream stream;
	stream.open(file.c_str(), std::ifstream::in);
	std::string line = "";

	std::string make, model;
	double engine, tankSize;
	int cylinders, cityMPG, highwayMPG;
	std::vector<Vehicle> vehicles;

	// Stream in each line and trim
	while (!stream.eof()) {
		getline(stream, line);

		// Trim line of extra whitespace
		line.erase(0, line.find_first_not_of(" \t\r\n"));

		// Check to see if it is a comment line
		if (line[0] != '#' && !line.empty()) {
			// Parse the line and create a vehicle object
			make = parseLine(line, 0, '|');
			model = parseLine(line, 1, '|');
			engine = std::atof(parseLine(line, 2, '|').c_str());
			cylinders = std::atoi(parseLine(line, 3, '|').c_str());
			tankSize = std::atof(parseLine(line, 4, '|').c_str());
			cityMPG = std::atoi(parseLine(line, 5, '|').c_str());
			highwayMPG = std::atoi(parseLine(line, 6, '|').c_str());
			vehicles.push_back(Vehicle(make, model, engine, cylinders, tankSize, cityMPG, highwayMPG));
		}
	}
	return vehicles;
}

