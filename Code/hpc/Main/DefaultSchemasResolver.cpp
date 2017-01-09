/**
 * @file DefaultSchemasResolver.cpp
 * @brief Implementation of methods for DefaultSchemasResolver.
 */

#include "DefaultSchemasResolver.h"

AbstractSchema * DefaultSchemasResolver::resolve(std::string key, double a, double dx, double dt)
{
	if (key == "upwind-explicit")
	{
		return new UpwindExplicitSchema(a, dx, dt);
	}
	else if (key == "upwind-implicit")
	{
		return new UpwindImplicitSchema(a, dx, dt);
	}
	else if (key == "crank-nicolson")
	{
		return new CrankNicolsonSchema(a, dx, dt);
	}
	
	throw new Exception();
}
