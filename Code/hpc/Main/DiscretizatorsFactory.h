/**
 * @file DiscretizatorsFactory.h
 * @brief Factory for creating discretizators.
 */

#ifndef __H_DISCRETIZATORS_FACTORY
#define __H_DISCRETIZATORS_FACTORY

#include "Discretizator.h"
#include "Configuration.h"

/** 
 * @brief Factory used for producing discretizators.
 * @author Mateusz Gasior
 */
class DiscretizatorsFactory
{
public:
	/**
	 * Produces discretizator in terms of given parameters.
	 * @param configuration Configuration of the file.
	 * @param coreId Current core id.
	 * @param coresQuantity Quantity of the cores.
	 * @return Discretizator for given parameters.
	 */
	Discretizator * manufacture(Configuration * configuration, long coreId, long coresQuantity);
};

#endif
