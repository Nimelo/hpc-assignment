#include "CrankNicolsonSchema.h"

void CrankNicolsonSchema::checkStabilityCondition()
{
	//TODO
}

std::vector<double>* CrankNicolsonSchema::apply(std::vector<double>* previousWave)
{
	//TODO
	return new std::vector<double>();
}

CrankNicolsonSchema::CrankNicolsonSchema(double a, double dx, double dt)
	: AbstractSchema(a, dx, dt)
{
}

std::vector<double>* CrankNicolsonSchema::postApplyAction(std::vector<double>* previousWave, double t)
{
	return new std::vector<double>();
}
