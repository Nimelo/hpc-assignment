/**
 * @file ImplicitUpwindParallelSchema.h
 * @brief Declaration of methods for ImplicitUpwindParallelSchema.
 */

#ifndef __H_IMPLICIT_UPWIND_PARALLEL_SCHEMA
#define __H_IMPLICIT_UPWIND_PARALLEL_SCHEMA

#include "AbstractSchema.h"


/**
 * @brief Implementaion of upwind implicit method in MPI.
 * @see AbstractSchema
 * Provides all methods that have to be used by discretizator.
 * @author Mateusz Gasior
 */
class ImplicitUpwindParallelSchema : public AbstractSchema
{
protected:
	/*
	 * Receives new lower bound for the solution for given parameters.
	 * @param coreId Current coreId.
	 * @param coresQuantity Quantity of reserved cores.
	 * @param bound To be returned if no other cores send messages.
	 * @return Return bound if it's main core, otherwise bound from next core.
	 */
	double getLowerBound(long coreId, long coresQuantity, double bound);
	
	/*
	 * Sends value to the next core. 
	 * If it is last core no message will be passed.
	 * @param coreId Current coreId.
	 * @param coresQuantity Quantity of reserved cores.
	 * @param value Value to be send.
	 */
	void sendUpperBound(long coreId, long coresQuantity, double value);
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
	ImplicitUpwindParallelSchema(long coreId, long coresQuantity, unsigned int numberOfPoints, double a, double dx, double dt);
	
	/**
	 * Checks the stability condition for given parameters.
	 * @throw StabilityConditionException if calculated coefficient (CFL) is greater than upper boundary.
	 */
	virtual void checkStabilityCondition();

	/**
	 * Applies schema for wave and given parameters.
	 * @param previousWave previousWave that is base for next time step discretization.
	 * @return Wave for next time step.
	 */
	virtual std::vector<double>* apply(std::vector<double>* previousWave);
};

#endif
