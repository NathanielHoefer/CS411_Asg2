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

#ifndef SRC_VEHICLERECORDS_HPP_
#define SRC_VEHICLERECORDS_HPP_

#include "Vehicle.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

class VehicleRecords
{
public:
	/*
	 * Imports and creates vehicle objects from the file passed
	 * 		Preconditions: File Format:
	 * 			Make|Model|EngineSize|EngineCylinders|TankSize|MpgCity|MpgHighway
	 * 			Lines beginning with '#' are treated as comments
	 * 		Postconditions: None
	 * 		Returns: Array containing all of the Vehicle objects
	 */
	static std::vector<Vehicle> importVehicles(std::string file);
};

#endif /* SRC_VEHICLERECORDS_HPP_ */
