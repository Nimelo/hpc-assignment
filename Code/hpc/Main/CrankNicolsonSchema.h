/**
 * @file CrankNicolsonSchema.h
 * @brief Declaration of methods for CrankNicolsonSchema.
 */

#ifndef __H_CRANK_NICOLSON_SCHEMA
#define __H_CRANK_NICOLSON_SCHEMA

#include <vector>
#include <algorithm>

#include "AbstractSchema.h"
#include "StabilityConditionException.h"

/**
* @brief Implementaion of Crank-Nicolson method.
* @see AbstractSchema
* Provides all methods that have to be used by discretizator.
* Stores calculated matrices for increasing performance.
* @author Mateusz Gasior
*/
class CrankNicolsonSchema : public AbstractSchema
{
protected:
	/*
	 * Array l.
	 */
	double * l;
	
	/*
	 * Array u.
	 */
	double * u;

	/*
	 * Array d.
	 */
	double * d;
public:

	/*
	 * Performs LU Decomposition for given parameters, which are elements in tridiagonal matrix.
	 * Sets the calculated values to l, u, d arrays.
	 * @param a Second diagonal value.
	 * @param b First diagonal value.
	 * @param c Third diagonal value.
	 */
	void createLUDecompositionFrom(double a, double b, double c);
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
	* @param numberOfPoints Number of points.
	* @param a Acceleration.
	* @param dx Delta x.
	* @param dt Delta t.
	*/
	CrankNicolsonSchema(long coreId, long coresQuantity, unsigned int numberOfPoints, double a, double dx, double dt);

	/*
	 * Default destructor. Deallocated l, u, d.
	 */
	~CrankNicolsonSchema();

	/**
	* Shifts wave by 2uT
	* @param previousWave wave for which post action will be applied.
	* @param t Current time.
	* @return Adjusted wave.
	*/
	virtual std::vector<double> * postApplyAction(std::vector<double> * previousWave, double t);

	/*
	 * Performs substitusion (backward and forward) in order to solve linear equation set stored in l,u,d and given q using Thomas algorithm.
	 * @param q Array of knowns.
	 * @return Vector of solution.
	 */
	std::vector<double> * ForwardAndBackWardSubstition(double *q);
};

#endif
