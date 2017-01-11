/**
 * @file AbstractSchema.cpp
 * @brief Implementation of methods for AbstractSchema.
 */

#include "AbstractSchema.h"

AbstractSchema::AbstractSchema(long coreId, long coresQuantity, unsigned int numberOfPoints, double a, double dx, double dt)
	: MPIObject(coreId, coresQuantity), accelertaion(a), deltaT(dt), deltaX(dx), numberOfPoints(numberOfPoints)
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
