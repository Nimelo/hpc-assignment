/**
 * @file DefaultSchemasResolver.cpp
 * @brief Implementation of methods for DefaultSchemasResolver.
 */

#include "DefaultSchemasResolver.h"
#include "Constants.h"

AbstractSchema * DefaultSchemasResolver::resolve(std::string key, long coreId, long coresQuantity, double a, double dx, double dt)
{
	if (key == Constants::UPWIND_EXPLICIT)
	{
		return new UpwindExplicitSchema(coreId, coresQuantity, a, dx, dt);
	}
	else if (key == Constants::UPWIND_IMPLICIT)
	{
		return new UpwindImplicitSchema(coreId, coresQuantity, a, dx, dt);
	}
	else if (key == Constants::CRANK_NICOLSON)
	{
		return new CrankNicolsonSchema(coreId, coresQuantity, a, dx, dt);
	}
	else if (key == Constants::UPWIND_EXPLICIT_PARALLEL)
	{
		return new ExplicitUpwindParallelSchema(coreId, coresQuantity, a, dx, dt);
	}
	else if (key == Constants::UPWIND_IMPLICIT_PARALLEL)
	{
		return new ImplicitUpwindParallelSchema(coreId, coresQuantity, a, dx, dt);
	}
		throw new Exception();
}
