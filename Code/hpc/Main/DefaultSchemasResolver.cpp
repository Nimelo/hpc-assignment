/**
 * @file DefaultSchemasResolver.cpp
 * @brief Implementation of methods for DefaultSchemasResolver.
 */

#include "DefaultSchemasResolver.h"

AbstractSchema * DefaultSchemasResolver::resolve(std::string key, long coreId, long coresQuantity, double a, double dx, double dt)
{
	if (key == "upwind-explicit")
	{
		return new UpwindExplicitSchema(coreId, coresQuantity, a, dx, dt);
	}
	else if (key == "upwind-implicit")
	{
		return new UpwindImplicitSchema(coreId, coresQuantity, a, dx, dt);
	}
	else if (key == "crank-nicolson")
	{
		return new CrankNicolsonSchema(coreId, coresQuantity, a, dx, dt);
	}
	else if (key == "upwind-explicit-parallel")
	{
		return new ExplicitUpwindParallelSchema(coreId, coresQuantity, a, dx, dt);
	}
		throw new Exception();
}
