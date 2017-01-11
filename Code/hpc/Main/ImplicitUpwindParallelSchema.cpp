/**
 * @file ImplicitUpwindParallelSchema.cpp
 * @brief Implementation of methods for ImplicitUpwindParallelSchema.
 */

#include "ImplicitUpwindParallelSchema.h"
#include "MPIWrapper.h"

double ImplicitUpwindParallelSchema::getLowerBound(long coreId, long coresQuantity, double bound)
{
	if (coreId == 0) {
		return bound;
	}
	else {
		return MPIWrapper::receiveSingleDoubleFromCore(coreId - 1, 0);
	}
}

void ImplicitUpwindParallelSchema::sendUpperBound(long coreId, long coresQuantity, double value)
{
	if (coreId != coresQuantity - 1)
	{
		MPIWrapper::sendDoublesToCore(coreId + 1, 0, &value, 1);
	}
}

ImplicitUpwindParallelSchema::ImplicitUpwindParallelSchema(long coreId, long coresQuantity, unsigned int numberOfPoints, double a, double dx, double dt)
	: AbstractSchema(coreId, coresQuantity, numberOfPoints, a, dx, dt)
{
}

void ImplicitUpwindParallelSchema::checkStabilityCondition()
{
}

std::vector<double>* ImplicitUpwindParallelSchema::apply(std::vector<double>* previousWave)
{
	unsigned int gridSize = previousWave->size();
	std::vector<double> * currentWave = new std::vector<double>(gridSize);

	double leftBound = this->getLowerBound(coreId, coresQuantity, previousWave->at(0));
	sendUpperBound(coreId, coresQuantity, previousWave->at(gridSize - 1));

	if (cfl > 0)
	{
		currentWave->at(0) = (previousWave->at(0) + cfl * leftBound) / (1.0 + cfl);
		for (unsigned int i = 1; i < gridSize; i++)
		{
			currentWave->at(i) = (previousWave->at(i) + cfl * currentWave->at(i - 1)) / (1.0 + cfl);
		}
	}
	else
	{
		for (unsigned int i = gridSize - 1; i >= 1; i--)
		{
			currentWave->at(i - 1) = ((1.0 + cfl) * currentWave->at(i) - previousWave->at(i)) / cfl;
		}
		currentWave->at(0) = ((1.0 + cfl) * currentWave->at(0) - previousWave->at(0)) / cfl;
	}

	return currentWave;
}
