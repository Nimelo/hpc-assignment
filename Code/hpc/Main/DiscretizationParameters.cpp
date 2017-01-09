/**
 * @file DiscretizationParameters.cpp
 * @brief Implementation of methods for DiscretizationParameters.
 */
#include "DiscretizationParameters.h"

DiscretizationParameters::DiscretizationParameters(double lowerBound, double upperBound,
	double acceleration,
	unsigned int meshSize, double(*analyticalFunction)(double, double, double),
	AbstractSchema * schema, std::vector<double> timeLevels,
	double dt, double dx)
	: lowerBound(lowerBound), upperBound(upperBound),
	 meshSize(meshSize), acceleration(acceleration), analyticalFunction(analyticalFunction),
	schema(schema), timeLevels(timeLevels),
	deltaT(dt), deltaX(dx)
{
}

DiscretizationParameters::~DiscretizationParameters()
{
	delete schema;
}
