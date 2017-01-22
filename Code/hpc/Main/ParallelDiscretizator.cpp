/**
 * @file ParallelDiscretizator.cpp
 * @brief Implementation of methods for ParallelDiscretizator.
 */

#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>

#include "ParallelDiscretizator.h"
#include "Exception.h"
#include "Constants.h"

long ParallelDiscretizator::getFragmentation(long coreId, long coresQuantity, long jobSize)
{
	if (coresQuantity == 1)
		return jobSize;
	else if (jobSize % coresQuantity == 0)
		return jobSize / coresQuantity;
	else
	{
		if (coreId == coresQuantity - 1)
			return jobSize / coresQuantity + jobSize % coresQuantity;
		else
			return jobSize / coresQuantity;
	}
}

std::vector<double>* ParallelDiscretizator::initializeSolution()
{
	std::vector<double> * solution = new std::vector<double>(fragmentation);
	double lowerBound = this->parameters->lowerBound + coreId * this->parameters->deltaX * floor(this->parameters->meshSize / coresQuantity);

	for (unsigned int i = 0; i < fragmentation; i++) {
		solution->at(i) = this->parameters->analyticalFunction(lowerBound + i * this->parameters->deltaX, 0.0, this->parameters->acceleration);
	}

	return solution;
}

void ParallelDiscretizator::gatherAndAddSolution(std::vector<double>* mainCoreSolution, DiscretizationResult * result, double time)
{
	double * finalSolution = new double[(this->parameters->meshSize)];
	double * index = finalSolution;

	for (long i = 0; i < fragmentation; i++)
	{
		finalSolution[i] = mainCoreSolution->at(i);
	}
		
	for (long i = 1; i < this->coresQuantity; i++)
	{
		long previousCoreFragmentation = getFragmentation(i - 1, coresQuantity, this->parameters->meshSize);
		index += previousCoreFragmentation;
		MPIWrapper::receiveDoublesFromCore(i, 1, getFragmentation(i, coresQuantity, this->parameters->meshSize), index);
	}

	std::vector<double> * copy = new std::vector<double>(finalSolution, finalSolution + this->parameters->meshSize);
	copy = this->parameters->schema->postApplyAction(copy, time);

	result->addWaves(time, copy, getAnalyticalWave(time));

	delete finalSolution;
}

ParallelDiscretizator::ParallelDiscretizator(long coreId, long coresQuantity, DiscretizationParameters * parameters)
	: Discretizator(coreId, coresQuantity, parameters)
{
	this->fragmentation = this->getFragmentation(coreId, coresQuantity, this->parameters->meshSize);
}

DiscretizationResult * ParallelDiscretizator::discretize()
{
	this->checkStabilityCondition();
	DiscretizationResult * result = NULL;

	if (coreId == Constants::ROOT_CORE)
	{
		result = new DiscretizationResult(this->parameters->lowerBound, this->parameters->upperBound, this->parameters->deltaX);
	}

	std::sort(this->parameters->timeLevels.begin(), this->parameters->timeLevels.end());
	std::vector<double> timeLevels(this->parameters->timeLevels);

	double time = 0.0;

	std::vector<double> * oldSolution = initializeSolution();

	while(timeLevels.size() > 0)
	{
		while (abs(time) < timeLevels.at(0))
		{
			try {
				std::vector<double> * newSolution = this->parameters->schema->apply(oldSolution);

				delete oldSolution;
				oldSolution = newSolution;
				time += this->parameters->deltaT;
			}
			catch (Exception & e)
			{
				delete oldSolution;
				if (coreId == Constants::ROOT_CORE)
				{
					delete result;
				}
				throw e;
			}
		}

		if (coreId == Constants::ROOT_CORE)
		{
			this->gatherAndAddSolution(oldSolution, result, time - this->parameters->deltaT);
		}
		else
		{
			MPIWrapper::sendDoublesToCore(Constants::ROOT_CORE, 1, &(*oldSolution)[0], fragmentation);
		}
		timeLevels.erase(timeLevels.begin());
	}

	delete oldSolution;

	return result;
}
