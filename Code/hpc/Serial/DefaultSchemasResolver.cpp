/**
 * @file DefaultSchemasResolver.cpp
 * @brief Implementation of methods for DefaultSchemasResolver.
 */

#include "DefaultSchemasResolver.h"

AbstractSchema * DefaultSchemasResolver::resolve(SchemasEnum key, double a, double dx, double dt)
{
	switch (key)
	{
	case UPWIND_EXPLICIT:
		return new UpwindExplicitSchema(a, dx, dt);
	case UPWIND_IMPLICIT:
		return new UpwindImplicitSchema(a, dx, dt);
	case CRANK_NICLOSON:
		return new CrankNicolsonSchema(a, dx, dt);
	}
}
