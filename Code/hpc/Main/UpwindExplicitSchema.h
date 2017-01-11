/**
 * @file UpwindExplicitSchema.h
 * @brief Declaration of methods for UpwindExplicitSchema.
 */

#ifndef __H_UPWIND_EXPLICIT_SCHEMA
#define __H_UPWIND_EXPLICIT_SCHEMA

#include <vector>

#include "AbstractSchema.h"
#include "StabilityConditionException.h"

/**
 * @brief Implementaion of upwind explicit method.
 * @see AbstractSchema
 * Provides all methods that have to be used by discretizator.
 * @author Mateusz Gasior
 */
class UpwindExplicitSchema : public AbstractSchema
{
public:
	/**
	* Explicitly defined constructor.
	* @param coreId Current core id.
	* @param coresQuantity Quantity of reserved cores.
	* @param numberOfPoints Number of points.
	* @param a Acceleration.
	* @param dx Delta x.
	* @param dt Delta t.
	*/
	UpwindExplicitSchema(long coreId, long coresQuantity, unsigned int numberOfPoints, double a, double dx, double dt);
	
	 /**
	 * Checks the stability condition for given parameters.
	 * @throw StabilityConditionException if calculated coefficient (CFL) is greater than upper boundary.
	 */
	void checkStabilityCondition();

	/**
	 * Applies schema for wave and given parameters.
	 * @param previousWave previousWave that is base for next time step discretization.
	 * @return Wave for next time step.
	 */
	std::vector<double> * apply(std::vector<double> * previousWave);
};

#endif
