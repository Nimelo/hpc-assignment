#ifndef __H_EXPLICIT_UPWIND_PARALLEL_SCHEMA
#define __H_EXPLICIT_UPWIND_PARALLEL_SCHEMA

#include "AbstractSchema.h"

class ExplicitUpwindParallelSchema : public AbstractSchema
{
protected:
	double getLowerBound(long coreId, long coresQuantity, double bound);
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
	ExplicitUpwindParallelSchema(long coreId, long coresQuantity, unsigned int numberOfPoints, double a, double dx, double dt);
	virtual void checkStabilityCondition();
	virtual std::vector<double>* apply(std::vector<double>* previousWave);
};

#endif
