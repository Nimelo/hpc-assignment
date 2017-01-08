/**
 * @file AbstractSchema.cpp
 * @brief Implementation of methods for AbstractSchema.
 */

#include "AbstractSchema.h"

AbstractSchema::AbstractSchema(double a, double dx, double dt)
	: accelertaion(a), deltaT(dt), deltaX(dx)
{
	cfl = accelertaion * deltaT / deltaX;
}

AbstractSchema::~AbstractSchema()
{

}

std::vector<double> * AbstractSchema::postApplyAction(std::vector<double>* previousWave, double t)
{
	return previousWave;
}
