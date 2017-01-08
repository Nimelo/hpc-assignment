/**
* @file Configuration.cpp
* @brief Implementation of methods for Configuration.
*/
#include "Configuration.h"

Configuration::Configuration(double lowerBound, double upperBound, double acceleration, SchemasEnum schema, unsigned int numberOfPoints, std::vector<double> timeLevels, double cfl)
	:lowerBound(lowerBound), upperBound(upperBound), acceleration(acceleration), schema(schema), numberOfPoints(numberOfPoints), timeLevels(timeLevels), cfl(cfl)
{
}
