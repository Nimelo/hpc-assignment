/**
 * @file WavePointsSummary.cpp
 * @brief Implementation of methods for WavePointsSummary.
 */

#include "WavePointsSummary.h"
#include <math.h>
#include <vector>

WavePointsSummary::WavePointsSummary(double time, std::vector<double> * numerical, std::vector<double> * analytical)
	: time(time), numerical(numerical), analytical(analytical)
{

}

WavePointsSummary::~WavePointsSummary()
{
	delete numerical;
	delete analytical;
}

double WavePointsSummary::errorNormInfinity() const
{
	double norm = fabs(this->analytical->at(0) - this->numerical->at(0));
	
	for (unsigned int i = 1; i < this->analytical->size(); i++)
	{
		double currentNorm = fabs(analytical->at(i) - numerical->at(i));
		if (currentNorm > norm)
			norm = currentNorm;
	}
	
	return norm;
}

double WavePointsSummary::errorNormOne() const
{
	double norm = 0.0;

	for (unsigned int i = 0; i < this->analytical->size(); i++)
	{
		norm += fabs(analytical->at(i) - numerical->at(i));
	}

	return norm / this->analytical->size();
}

double WavePointsSummary::errorNormTwo() const
{
	double norm = 0.0;

	for (unsigned int i = 0; i < this->analytical->size(); i++)
	{
		norm += pow(analytical->at(i) - numerical->at(i), 2);
	}

	return sqrt(norm);
}
