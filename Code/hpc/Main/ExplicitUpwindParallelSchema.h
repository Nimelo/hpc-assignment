#ifndef __H_EXPLICIT_UPWIND_PARALLEL_SCHEMA
#define __H_EXPLICIT_UPWIND_PARALLEL_SCHEMA

#include "AbstractSchema.h"

class ExplicitUpwindParallelSchema : public AbstractSchema
{
protected:
	double getLowerBound(long coreId, long coresQuantity, double bound);
	void sendUpperBound(long coreId, long coresQuantity, double value);
public:
	virtual void checkStabilityCondition();
	virtual std::vector<double>* apply(std::vector<double>* previousWave);
};

#endif
