#ifndef __H_IMPLICIT_UPWIND_PARALLEL_SCHEMA
#define __H_IMPLICIT_UPWIND_PARALLEL_SCHEMA

#include "AbstractSchema.h"

class ImplicitUpwindParallelSchema : public AbstractSchema
{
protected:
	double getLowerBound(long coreId, long coresQuantity, double bound);
	void sendUpperBound(long coreId, long coresQuantity, double value);
public:
	ImplicitUpwindParallelSchema(long coreId, long coresQuantity, double a, double dx, double dt);
	virtual void checkStabilityCondition();
	virtual std::vector<double>* apply(std::vector<double>* previousWave);
};

#endif
