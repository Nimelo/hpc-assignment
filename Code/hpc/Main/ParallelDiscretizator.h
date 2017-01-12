/**
 * @file ParallelDiscretizator.h
 * @brief Declaration of methods for ParallelDiscretizator.
 */
#ifndef __H_PARALLEL_DISCRETIZATOR
#define __H_PARALLEL_DISCRETIZATOR

#include <vector>

#include "Discretizator.h"
#include "MPIWrapper.h"


/**
 * @brief Tool for solving discretization problem given by parameters in parallel using MPI.
 * @see Discretizator
 * @author Mateusz Gasior
 */
class ParallelDiscretizator : public Discretizator
{
protected:
	/**
	 * Fragmentation of current discretizator (local grid size).
	 */
	long fragmentation;
	
	/**
	 * Calculates fragmentation for given parameters.
	 * @param coreId Core id.
	 * @param coreQuantity Quantity of cores.
	 * @param jobSize Size of the job.
	 * @return Fragmentation for given parameters.
	 */
	long getFragmentation(long coreId, long coreQuantity, long jobSize);

	/**
	 * Returns initialized vector of values by initialization function stored in configuration.	
	 * @return Fragment of initialization solution (vector).
	 */
	std::vector<double> * initializeSolution();

	/**
	 * Gathers partials results from cores and stores them in the result.
	 * @param mainCoreSolution Partial solution of main (root) core.
	 * @param result Result for the whole discretization process.
	 * @param time Time for solution.
	 */
	void gatherAndAddSolution(std::vector<double> * mainCoreSolution, DiscretizationResult * result, double time);
public:
	/**
	 * Overridden constructor for explicitly given parameters.
	 * @param coreId Current core id.
	 * @param coresQuantity Quantity of cores.
	 * @param parameters Discretization parameters.
	 */
	ParallelDiscretizator(long coreId, long coresQuantity, DiscretizationParameters * parameters);
	
	/**
	 * Performs discretization process for given parameters and produces result.
	 * @return Result of discretization.
	 */
	DiscretizationResult * discretize();
};

#endif
