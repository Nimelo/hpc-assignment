/**
 * @file UpwindExplicitSchema.cpp
 * @brief Implementation of methods for UpwindExplicitSchema.
 */
 
#include "UpwindExplicitSchema.h"

UpwindExplicitSchema::UpwindExplicitSchema(long coreId, long coresQuantity, unsigned int numberOfPoints, double a, double dx, double dt)
	: AbstractSchema(coreId, coresQuantity, numberOfPoints, a, dx, dt)
{
}

void UpwindExplicitSchema::checkStabilityCondition()
{
	if (cfl > 1.0)
	{
		throw StabilityConditionException();
	}
}

std::vector<double>* UpwindExplicitSchema::apply(std::vector<double>* previousWave)
{
	unsigned int gridSize = previousWave->size();

	std::vector<double> * currentWave = new std::vector<double>(gridSize);

	currentWave->at(0) = previousWave->at(0);
	currentWave->at(gridSize - 1) = previousWave->at(gridSize - 1);

	for (unsigned int i = 1; i < gridSize - 1; i++)
	{
		currentWave->at(i) = previousWave->at(i) - cfl * (previousWave->at(i) - previousWave->at(i - 1));
	}

	return currentWave;
}
