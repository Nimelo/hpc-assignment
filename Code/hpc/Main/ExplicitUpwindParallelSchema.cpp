#include "ExplicitUpwindParallelSchema.h"
#include "MPIWrapper.h"

double ExplicitUpwindParallelSchema::getLowerBound(long coreId, long coresQuantity, double bound)
{
	if (coreId == 0) {
		return bound;
	}
	else {
		return MPIWrapper::receiveSingleDoubleFromCore(coreId - 1, 0);
	}
}

void ExplicitUpwindParallelSchema::sendUpperBound(long coreId, long coresQuantity, double value)
{
	if (coreId != coresQuantity - 1)
	{
		MPIWrapper::sendDoublesToCore(coreId + 1, 0, &value, 1);
	}
}

ExplicitUpwindParallelSchema::ExplicitUpwindParallelSchema(long coreId, long coresQuantity, unsigned int numberOfPoints, double a, double dx, double dt)
	: AbstractSchema(coreId, coresQuantity, numberOfPoints, a, dx, dt)
{
}

void ExplicitUpwindParallelSchema::checkStabilityCondition()
{
}

std::vector<double>* ExplicitUpwindParallelSchema::apply(std::vector<double>* previousWave)
{
	unsigned int gridSize = previousWave->size();
	std::vector<double> * currentWave = new std::vector<double>(gridSize);

	double leftBound = this->getLowerBound(coreId, coresQuantity, previousWave->at(0));

	currentWave->at(0) = previousWave->at(0) - cfl * (previousWave->at(0) - leftBound);
	sendUpperBound(coreId, coresQuantity, previousWave->at(gridSize - 1));

	for (unsigned int i = 1; i < gridSize; i++)
	{
		currentWave->at(i) = previousWave->at(i) - cfl * (previousWave->at(i) - previousWave->at(i - 1));
	}

	return currentWave;
}
