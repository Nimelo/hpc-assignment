#ifndef __H_ABSTRACT_DISCRETIZATOR
#define __H_ABSTRACT_DISCRETIZATOR

#include <vector>

#include "DiscretizationResult.h"

class AbstractDiscretizator
{
protected:
	virtual std::vector<double> * getAnalyticalWave(double time) = 0;
	virtual void checkStabilityCondition() = 0;
public:
	virtual ~AbstractDiscretizator();
	virtual DiscretizationResult * discretize() = 0;
};

#endif