/**
 * @file DiscretizationResult.cpp
 * @brief Implementation of methods for DiscretizationResult.
 */

#include <vector>
#include "DiscretizationResult.h"

#include <vector>

DiscretizationResult::DiscretizationResult(double lowerBound, double upperBound, double deltaX)
	: lowerBound(lowerBound), upperBound(upperBound), deltaX(deltaX)
{
	this->summaries = new WavesSummary(lowerBound, upperBound, deltaX);
}


DiscretizationResult::~DiscretizationResult()
{
	delete this->summaries;
}

WavesSummary * DiscretizationResult::getValuesAtTimeT() const
{
	return this->summaries;
}

NormSummary * DiscretizationResult::getNorms() 
{
	NormSummary * summary = new NormSummary();
	for (WavesSummary::iterator it = this->summaries->begin(); it != this->summaries->end(); ++it)
	{
		summary->push_back(NormsPerTimeLevel((*it)->time, (*it)->errorNormInfinity(), (*it)->errorNormOne(), (*it)->errorNormTwo()));
	}

	return summary;
}

void DiscretizationResult::addWaves(double time, std::vector<double> * numerical, std::vector<double> * analytical)
{
	this->summaries->push_back(new WavePointsSummary(time, numerical, analytical));
}
