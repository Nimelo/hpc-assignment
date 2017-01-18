/**
 * @file DiscretizatorsFactory.cpp
 * @brief Implementation of methods for DiscretizatorsFactory.
 */

#include "DiscretizatorsFactory.h"
#include "AnalyticalFunctions.h"
#include "DefaultSchemasResolver.h"

#include "DiscretizationParameters.h"
#include "Discretizator.h"
#include "ParallelDiscretizator.h"

#include "DiscretizationResult.h"
#include "Exception.h"
#include "ConfigurationLoadingException.h"
#include "DiscretizationParameters.h"
#include "DefaultSchemasResolver.h"
#include "Constants.h"

#include <string>

Discretizator * DiscretizatorsFactory::manufacture(Configuration * configuration, long coreId, long coresQuantity)
{
	DefaultSchemasResolver dsr;

	double dx = (configuration->upperBound - configuration->lowerBound) / configuration->numberOfPoints;
	double dt = (configuration->cfl * dx) / configuration->acceleration;

	int fragmentation = coresQuantity == 1 ?
			configuration->numberOfPoints :
			configuration->numberOfPoints % coresQuantity == 0 ?
				configuration->numberOfPoints / coresQuantity :
				coreId == coresQuantity - 1 ?
					configuration->numberOfPoints / coresQuantity + configuration->numberOfPoints % coresQuantity :
					configuration->numberOfPoints / coresQuantity;
					
	DiscretizationParameters * discretizationParameters = new DiscretizationParameters(
		configuration->lowerBound,
		configuration->upperBound,
		configuration->acceleration,
		(long)configuration->numberOfPoints,
		AnalyticalFunctions::expFunction,
		dsr.resolve(configuration->schema, coreId, coresQuantity, fragmentation, configuration->acceleration, dx, dt),
		configuration->timeLevels,
		dt,
		dx
	);

	std::string schema = configuration->schema;
	if (std::string(Constants::UPWIND_EXPLICIT) == schema
		|| std::string(Constants::UPWIND_IMPLICIT) == schema
		|| std::string(Constants::CRANK_NICOLSON) == schema
		|| std::string(Constants::CRANK_NICOLSON_LAPACK) == schema)
	{
		return new Discretizator(coreId, coresQuantity, discretizationParameters);
	}
	else if (std::string(Constants::UPWIND_EXPLICIT_PARALLEL) == schema
		|| std::string(Constants::UPWIND_IMPLICIT_PARALLEL) == schema
		|| std::string(Constants::CRANK_NICOLSON_PARALLEL) == schema)
	{
		return new ParallelDiscretizator(coreId, coresQuantity, discretizationParameters);
	}
	else
	{
		delete discretizationParameters;
		throw Exception();
	}
}
