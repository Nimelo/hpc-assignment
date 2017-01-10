/**
* @file UpwindImplicitSchema.h
* @brief Declaration of methods for UpwindImplicitSchema.
*/

#ifndef __H_UPWIND_IMPLICIT_SCHEMA
#define __H_UPWIND_IMPLICIT_SCHEMA

#include <vector>
#include <algorithm>

#include "AbstractSchema.h"
#include "StabilityConditionException.h"

/**
 * @brief Implementaion of upwind implicit method.
 * @see AbstractSchema
 * Provides all methods that have to be used by discretizator.
 * Stores calculated matrices for increasing performance.
 * @author Mateusz Gasior
 */
class UpwindImplicitSchema : public AbstractSchema
{
public:

	/**
	* Checks the stability condition for given parameters.
	* @throw StabilityConditionException if calculated coefficient (CFL) is negative.
	*/
	void checkStabilityCondition();

	/**
	* Applies schema for wave and given parameters.
	* @param previousWave previousWave that is base for next time step discretization.
	* @return Wave for next time step.
	*/
	std::vector<double> * apply(std::vector<double> * previousWave);

	/**
	* Explicitly defined constructor.
	* @param coreId Current core id.
	* @param coresQuantity Quantity of reserved cores.
	* @param a Acceleration.
	* @param dx Delta x.
	* @param dt Delta t.
	*/
	UpwindImplicitSchema(long coreId, long coresQuantity, double a, double dx, double dt);

	/**
	 * Shifts wave by 2uT
	 * @param previousWave wave for which post action will be applied.
	 * @param t Current time.
	 * @return Adjusted wave.
	 */
	virtual std::vector<double> * postApplyAction(std::vector<double> * previousWave, double t);
};

#endif
