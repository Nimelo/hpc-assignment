/**
 * @file Discretizator.h
 * @brief Declaration of methods for Discretizator.
 */
#ifndef __H_DISCRETIZATOR
#define __H_DISCRETIZATOR

#include <vector>

#include "DiscretizationParameters.h"
#include "DiscretizationResult.h"

/**
 * @brief Tool for solving discretization problem given by parameters.
 * @author Mateusz Gasior
 */
class Discretizator
{
protected:

	/**
	 * Parameters for discretization.
	 */
	DiscretizationParameters * parameters;

	/**
	 * Return analytical wave for given time.
	 * @param time Time for calculating analytical wave.
	 * @return Analytical wave for given time.
	 */
	std::vector<double> * getAnalyticalWave(double time) const;

	/**
	 * Invokes stability condition function from schema that is in parameters.
	 * @throw StabilityConditionException if calculated coefficient (CFL) makes schema unstable. 
	 */
	void checkStabilityCondition() const;
public:

	/**
	 * Overridden constructor for explicitly given parameters.
	 * @param parameters Discretization parameters.
	 */
	Discretizator(DiscretizationParameters * parameters);

	/**
	 * Default destructor.
	 */
	virtual ~Discretizator();
	
	/**
	 * Performs discretization process for given parameters and produces result.
	 * @return Result of discretization.
	 */
	virtual DiscretizationResult * discretize();
};

#endif