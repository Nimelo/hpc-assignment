/**
* @file Discretizator.cpp
* @brief Implementation of methods for Discretizator.
*/

#include <algorithm>
#include <vector>

#include "Discretizator.h"
#include "Exception.h"

std::vector<double> * Discretizator::getAnalyticalWave(double time) const
{
	double lb = this->parameters->lowerBound;
	double ub = this->parameters->upperBound;
	double dx = this->parameters->deltaX;
	double a = this->parameters->acceleration;

	unsigned int gridSize = this->parameters->meshSize;
	std::vector<double> * wave = new std::vector<double>(gridSize);

	for (unsigned int i = 0; i < (unsigned int)gridSize; i++)
	{
		wave->at(i) = this->parameters->analyticalFunction(lb + i * dx, time, a);
	}

	return wave;
}

void Discretizator::checkStabilityCondition() const
{
	this->parameters->schema->checkStabilityCondition();
}

Discretizator::Discretizator(DiscretizationParameters * parameters)
	: parameters(parameters)
{
}


Discretizator::~Discretizator()
{
	delete this->parameters;
}

DiscretizationResult * Discretizator::discretize()
{
	this->checkStabilityCondition();
	DiscretizationResult * result = new DiscretizationResult(this->parameters->lowerBound, this->parameters->upperBound, this->parameters->deltaX);
	std::sort(this->parameters->timeLevels.begin(), this->parameters->timeLevels.end());

	std::vector<double> timeLevels(this->parameters->timeLevels);

	double time = 0.0;
	std::vector<double> * previousWave = getAnalyticalWave(time);

	while (timeLevels.size() > 0)
	{
		while (abs(time) < timeLevels.at(0))
		{
			try {
				std::vector<double> * currentWave = this->parameters->schema->apply(previousWave);
				delete previousWave;
				previousWave = currentWave;
				time += this->parameters->deltaT;
			}
			catch (Exception & e)
			{
				delete previousWave;
				delete result;
				throw e;
			}		
		}
		
		std::vector<double> * copy = new std::vector<double>((*previousWave).begin(), (*previousWave).end());
		copy = this->parameters->schema->postApplyAction(copy, time - this->parameters->deltaT);

		result->addWaves(time - this->parameters->deltaT, copy, getAnalyticalWave(time - this->parameters->deltaT));
		timeLevels.erase(timeLevels.begin());
	}
	
	delete previousWave;
	return result;
}
