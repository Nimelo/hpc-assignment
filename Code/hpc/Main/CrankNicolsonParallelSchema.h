/**
 * @file CrankNicolsonParallelSchema.h
 * @brief Declaration of methods for CrankNicolsonParallelSchema.
 */

#ifndef __H_CRANK_NICOLSON_PARALLEL_SCHEMA
#define __H_CRANK_NICOLSON_PARALLEL_SCHEMA

#include <vector>
#include <algorithm>

#include "AbstractSchema.h"
#include "StabilityConditionException.h"

/**
* @brief Implementaion of Crank-Nicolson method in MPI.
* @see AbstractSchema
* Provides all methods that have to be used by discretizator.
* Stores calculated matrices for increasing performance.
* @author Mateusz Gasior
*/
class CrankNicolsonParallelSchema : public AbstractSchema
{
private:
	/*
	 * MPI Tag message - left.
	 */
	const long TAG_LEFT;
	/*
	 * MPI Tag message - right.
	 */
	const long TAG_RIGHT;
	/*
	 * MPI Tag message - d.
	 */
	const long TAG_D;
	/*
	 * MPI Tag message - z.
	 */
	const long TAG_Z;
	/*
	 * MPI Tag message - y.
	 */
	const long TAG_Y;
	/*
	 * MPI Tag message - l.
	 */
	const long TAG_L;
protected:
	/*
	 * Pointers to arrays used in Thomas algorithm for solving tridiagonal matrices.
	 */
	double * l, * u, * d;
	
	/*
	 * Performs LU Decomposition for given parameters, which are elements in tridiagonal matrix.
	 * Sets the calculated values to l, u, d arrays.
	 * @param a Second diagonal value.
	 * @param b First diagonal value.
	 * @param c Third diagonal value.
	 */
	void setUpLUDecomposition(double a, double b, double c);
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
	* @param numberOfPoints Number of points.
	* @param a Acceleration.
	* @param dx Delta x.
	* @param dt Delta t.
	*/
	CrankNicolsonParallelSchema(long coreId, long coresQuantity, unsigned int numberOfPoints, double a, double dx, double dt);

	/**
	* Shifts wave by 2uT
	* @param previousWave wave for which post action will be applied.
	* @param t Current time.
	* @return Adjusted wave.
	*/
	virtual std::vector<double> * postApplyAction(std::vector<double> * previousWave, double t);

	/*
	 * Default destructor. Deallocates l, u, d arrays.
	 */
	~CrankNicolsonParallelSchema();

	/*
	 * Performs substitusion (backward and forward) in order to solve linear equation set stored in l,u,d and given q using Thomas algorithm.
	 * @param q Array of knowns.
	 * @return Vector of solution.
	 */
	std::vector<double> * Substitution(double *q);

	/*
	 * Part of Thomas algorithm for solving tridiagonal matrices problem.
	 * Performs forward substitusion on given array.
	 * @param q Array of knowns.
	 * @return Vector of solution.
	 */
	double * ForwardSubstitution(double *q);
	
	/*
	 * Part of Thomas algorithm for solving tridiagonal matrices problem.
	 * Performs forward substitusion on given array.
	 * @param y Array of knowns.
	 * @return Vector of solution.
	 */
	std::vector<double> * BackwardSubstitution(double *y);
};

#endif
