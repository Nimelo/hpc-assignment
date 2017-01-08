/**
 * @file AnalyticalFunctions.cpp
 * @brief Implementation of methods for AnalyticalFunctions.
 */

#include "AnalyticalFunctions.h"
#include <math.h>

double AnalyticalFunctions::expFunction(double x, double t, double a)
{
	return 0.5 * exp(-(x - a * t) * (x - a * t));
}

