/**
 * @file AbstractSchema.h
 * @brief Declaration of methods for AbstractSchema.
 */

#ifndef __H_ABSTRACT_SCHEMA
#define __H_ABSTRACT_SCHEMA

#include <vector>

/**
 * @brief Abstraction for schema.
 * Provides all methods that have to be used by discretizator.
 * @author Mateusz Gasior
 */
class AbstractSchema
{
protected:

	/**
	 * Acceleration.
	 */
	double accelertaion;

	/**
	 * Delta X.
	 */
	double deltaX;

	/**
	 * Delta T.
	 */
	double deltaT;

	/**
	 * CFL number.
	 */
	double cfl;
public:

	/**
	 * Explicitly defined constructor.
	 * @param a Acceleration.
	 * @param dx Delta x.
	 * @param dt Delta t.
	 */	 
	explicit AbstractSchema(double a, double dx, double dt);

	/**
	 * Default destructor.
	 */
	virtual ~AbstractSchema();

	/**
	 * Checks the stability condition for given parameters.
	 * @throw StabilityConditionException if calculated coefficient (CFL) is greater than upper boundary.
	 */
	virtual void checkStabilityCondition() = 0;

	/**
	 * Applies schema for wave and given parameters.
	 * @param previousWave previousWave that is base for next time step discretization.
	 * @return Wave for next time step.
	 */
	virtual std::vector<double> * apply(std::vector<double> * previousWave) = 0;

	/**
	 * Performs post applygin action for given wave.
	 * @param previousWave wave for which post action will be applied.
	 * @param t Current time level.
	 * @return Adjusted wave.
	 */
	virtual std::vector<double> * postApplyAction(std::vector<double> * previousWave, double t);
};

#endif
