#ifndef __H_CRANK_NICOLSON_PARALLEL_SCHEMA
#define __H_CRANK_NICOLSON_PARALLEL_SCHEMA

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
class CrankNicolsonParallelSchema : public AbstractSchema
{
private:
	long TAG_LEFT = 0;
	long TAG_RIGHT = 1;
	long TAG_D = 2;
	long TAG_Z = 3;
	long TAG_Y = 4;
	long TAG_L = 5;
public:
	void sendLeftBound(double value);
	double recvLeftBound(double bound);
	void sendRightBound(double value);
	double recvRightBound(double bound);
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
	CrankNicolsonParallelSchema(long coreId, long coresQuantity, double a, double dx, double dt);

	/**
	* Shifts wave by 2uT
	* @param previousWave wave for which post action will be applied.
	* @param t Current time.
	* @return Adjusted wave.
	*/
	virtual std::vector<double> * postApplyAction(std::vector<double> * previousWave, double t);

	void ThomasAlgorithm(int N, double b, double a, double c, double *x, double *q);
};

#endif
