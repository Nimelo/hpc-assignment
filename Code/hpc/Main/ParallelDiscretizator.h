#ifndef __H_PARALLEL_DISCRETIZATOR
#define __H_PARALLEL_DISCRETIZATOR

#include <vector>

#include "Discretizator.h"
#include "MPIWrapper.h"

class ParallelDiscretizator : public Discretizator
{
protected:
	long coreId;
	long coresQuantity;
	long fragmentation;
	long mainCoreId;

	long getFragmentation(long coreId, long coreQuantity, long jobSize);
	std::vector<double> * initializeSolution();
	void gatherAndAddSolution(std::vector<double> * mainCoreSolution, DiscretizationResult * result, double time);
public:
	ParallelDiscretizator(DiscretizationParameters * parameters);
	DiscretizationResult * discretize();
};

#endif