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
	unsigned int counter = 0;

	while(point < ws.upperBound)
	{
		os << point << separator;
		for (WavesSummary::const_iterator it = ws.begin(); it != ws.end(); ++it)
		{
			os << (*it)->numerical->at(counter) << separator;
			os << (*it)->analytical->at(counter) << separator;
		}
		
		os << std::endl;
		++counter;
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
