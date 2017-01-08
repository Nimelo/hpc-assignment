/**
 * @file WavesSummary.cpp
 * @brief Implementation of methods for WavesSummary.
 */

#include "WavesSummary.h"
#include <vector>

std::ostream & operator<<(std::ostream & os, const WavesSummary & ws)
{
	const char separator = ',';

	os << std::endl << "X" << separator;

	for (WavesSummary::const_iterator it = ws.begin(); it != ws.end(); ++it)
	{
		os << "Numerical t = " << (*it)->time << separator << "Analytical t = " << (*it)->time << separator;
	}

	os << std::endl;

	double point = ws.lowerBound;
	unsigned int size = ws[0]->analytical->size();

	for (unsigned int i = 0; i < size; i++)
	{
		os << point << separator;
		for (WavesSummary::const_iterator it = ws.begin(); it != ws.end(); ++it)
		{
			os << (*it)->numerical->at(i) << separator;
			os << (*it)->analytical->at(i) << separator;
		}

		os << std::endl;
		point += ws.deltaX;
	}

	return os;
}

WavesSummary::WavesSummary(double lowerBound, double upperBound, double deltaX)
	: lowerBound(lowerBound), upperBound(upperBound), deltaX(deltaX)
{
}

WavesSummary::~WavesSummary()
{
	for (WavesSummary::iterator it = this->begin(); it != this->end(); ++it)
	{
		delete (*it);
	}
}
