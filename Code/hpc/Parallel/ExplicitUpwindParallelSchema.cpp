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

void ExplicitUpwindParallelSchema::checkStabilityCondition()
{
}

std::vector<double>* ExplicitUpwindParallelSchema::apply(std::vector<double>* previousWave)
{
	unsigned int gridSize = previousWave->size();
	std::vector<double> * currentWave = new std::vector<double>(gridSize);
	long coreId = MPIWrapper::getCoreId();
	long coresQuantity = MPIWrapper::getQuantityOfCores();

	double leftBound = this->getLowerBound(coreId, coresQuantity, previousWave->at(0));

	currentWave->at(0) = previousWave->at(0) - cfl * (previousWave->at(0) - leftBound);
	sendUpperBound(coreId, coresQuantity, previousWave->at(gridSize - 1));
		
	for (unsigned int i = 1; i < gridSize; i++)
	{
		currentWave->at(i) = previousWave->at(i) - cfl * (previousWave->at(i) - previousWave->at(i - 1));
	}

	return currentWave;
}
