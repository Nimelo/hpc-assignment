/**
 * @file NormSummary.cpp
 * @brief Implementation of methods for NormSummary.
 */
#include "NormSummary.h"

std::ostream & operator<<(std::ostream & os, const NormSummary & ns)
{
	const char separator = ',';
	os << "T" << separator;
	os << "Norm Infinity" << separator;
	os << "Norm One" << separator;
	os << "Norm Two" << separator;
	os << std::endl;

	for (NormSummary::const_iterator it = ns.begin(); it != ns.end(); ++it)
	{
		os << (*it).time << separator;
		os << (*it).normInfinity << separator;
		os << (*it).normOne << separator;
		os << (*it).normTwo << separator;
		os << std::endl;
	}

	return os;
}
