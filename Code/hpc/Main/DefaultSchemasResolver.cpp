/**
 * @file DefaultSchemasResolver.cpp
 * @brief Implementation of methods for DefaultSchemasResolver.
 */

#include "DefaultSchemasResolver.h"
#include "Constants.h"

AbstractSchema * DefaultSchemasResolver::resolve(std::string key, long coreId, long coresQuantity, unsigned int numberOfPoints, double a, double dx, double dt)
{
	if (key == Constants::UPWIND_EXPLICIT)
	{
		return new UpwindExplicitSchema(coreId, coresQuantity, numberOfPoints, a, dx, dt);
	}
	else if (key == Constants::UPWIND_IMPLICIT)
	{
		return new UpwindImplicitSchema(coreId, coresQuantity, numberOfPoints, a, dx, dt);
	}
	else if (key == Constants::CRANK_NICOLSON)
	{
		return new CrankNicolsonSchema(coreId, coresQuantity, numberOfPoints, a, dx, dt);
	}
	else if (key == Constants::UPWIND_EXPLICIT_PARALLEL)
	{
		return new ExplicitUpwindParallelSchema(coreId, coresQuantity, numberOfPoints, a, dx, dt);
	}
	else if (key == Constants::UPWIND_IMPLICIT_PARALLEL)
	{
		return new ImplicitUpwindParallelSchema(coreId, coresQuantity, numberOfPoints, a, dx, dt);
	}
	else if (key == Constants::CRANK_NICOLSON_PARALLEL)
	{
		return new CrankNicolsonParallelSchema(coreId, coresQuantity, numberOfPoints, a, dx, dt);
	}
	else if (key == Constants::CRANK_NICOLSON_LAPACK)
	{
		return new CrankNicolsonSchemaEigen(coreId, coresQuantity, numberOfPoints, a, dx, dt);
	}
		throw new Exception();
}
