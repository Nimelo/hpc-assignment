#ifndef __H_PARALLEL_EXPLICIT_DISCRETIZATOR
#define __H_PARALLEL_EXPLICIT_DISCRETIZATOR

#include "AbstractDiscretizator.h"
#include "DiscretizationParameters.h"

class ParallelExplicitDiscretizator : AbstractDiscretizator
{
private:
	long coreId;
	long coreQuantity;

	/**
	 * Parameters for discretization.
	 */
	DiscretizationParameters * parameters;
protected:
	virtual std::vector<double>* getAnalyticalWave(double time);
	virtual void checkStabilityCondition();
public:
	virtual DiscretizationResult * discretize();
};

#endif