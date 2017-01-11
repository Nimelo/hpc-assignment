/**
 * @file UpwindImplicitSchema.cpp
 * @brief Implementation of methods for UpwindImplicitSchema.
 */

#include "UpwindImplicitSchema.h"
#include <cmath>

void UpwindImplicitSchema::checkStabilityCondition()
{
	if (cfl == 0)
		throw StabilityConditionException();
}

std::vector<double>* UpwindImplicitSchema::apply(std::vector<double>* previousWave)
{
	unsigned int gridSize = previousWave->size();

	std::vector<double> * currentWave = new std::vector<double>(gridSize);

	currentWave->at(0) = previousWave->at(0);
	//currentWave->at(gridSize - 1) = previousWave->at(gridSize - 1);

	if (cfl > 0)
	{
		for (unsigned int i = 1; i < gridSize; i++)
		{
			currentWave->at(i) = (previousWave->at(i) + cfl * currentWave->at(i - 1)) / (1.0 + cfl);
		}
	}
	else
	{
		for (unsigned int i = gridSize - 1; i >= 2; i--)
		{
			currentWave->at(i - 1) = ((1.0 + cfl) * currentWave->at(i) - previousWave->at(i)) / cfl;
		}
	}


	return currentWave;
}

UpwindImplicitSchema::UpwindImplicitSchema(long coreId, long coresQuantity, unsigned int numberOfPoints, double a, double dx, double dt)
	: AbstractSchema(coreId, coresQuantity, numberOfPoints, a, dx, dt)
{
}

std::vector<double>* UpwindImplicitSchema::postApplyAction(std::vector<double>* previousWave, double t)
{
	double coefficient = (this->accelertaion * this->deltaT) / this->deltaX;
	if (coefficient < 0)
	{
		unsigned int offset = std::ceil(2 * (1.0 / this->deltaX) * -1 * this->accelertaion * t);

		for (unsigned int i = 0; i < offset; i++)
		{
			for (unsigned int j = previousWave->size() - 1; j >= 1; j--)
			{
				(*previousWave)[j] = (*previousWave)[j - 1];
			}
		}
	}
	return previousWave;
}
