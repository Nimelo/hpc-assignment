/**
 * @file DefaultSchemasResolver.h
 * @brief Declaration of methods for DefaultSchemasResolver.
 */

#ifndef __H_DEFAULT_SCHEMAS_RESOLVER
#define __H_DEFAULT_SCHEMAS_RESOLVER

#include "SchemasEnum.h"
#include "AbstractSchema.h"

#include "UpwindExplicitSchema.h"
#include "UpwindImplicitSchema.h"
#include "CrankNicolsonSchema.h"

/**
 * @brief Default resolver for schemas.
 * @see AbstractSchemasResolver
 * @author Mateusz Gasior
 */
class DefaultSchemasResolver
{
public:
	/**
	 * Resolves schema by given key.
	 * @see SchemasEnum
	 * @param key Key for schema.
	 * @param a Acceleration.
	 * @param dx Delta X.
	 * @param dt Delta T.
	 * @return Schema corresponding to the given key.
	 */
	AbstractSchema * resolve(std::string key, double a, double dx, double dt);
};

#endif
