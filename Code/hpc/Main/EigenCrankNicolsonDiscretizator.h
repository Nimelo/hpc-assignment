/**
 * @file EigenCrankNicolsonDiscretizator.h
 * @brief Declaration of methods for EigenCrankNicolsonDiscretizator.
 */
#ifndef __H_DISCRETIZATOR_EIGEN
#define __H_DISCRETIZATOR_EIGEN

#include <vector>
#include <Eigen>

#include "MPIObject.h"
#include "DiscretizationParameters.h"
#include "DiscretizationResult.h"

/**
 * @brief Tool for solving discretization problem given by parameters using EIGEN library.
 * @author Mateusz Gasior
 */
class EigenCrankNicolsonDiscretizator
{
protected:

	/**
	 * Parameters for discretization.
	 */
	DiscretizationParameters * parameters;

	/**
	 * Return analytical wave for given time.
	 * @param time Time for calculating analytical wave.
	 * @return Analytical wave for given time.
	 */
	std::vector<double> * getAnalyticalWave(double time) const;

	/**
	* Return analytical wave for given time.
	* @param time Time for calculating analytical wave.
	* @return Analytical wave for given time.
	*/
	Eigen::VectorXd getAnalyticalWaveEigen(double time) const;

	/**
	 * Invokes stability condition function from schema that is in parameters.
	 * @throw StabilityConditionException if calculated coefficient (CFL) makes schema unstable. 
	 */
	void checkStabilityCondition() const;
public:

	/**
	 * Overridden constructor for explicitly given parameters.
	 * @param coreId Current core id.
	 * @param coresQuantity Quantity of cores.
	 * @param parameters Discretization parameters.
	 */
	EigenCrankNicolsonDiscretizator(DiscretizationParameters * parameters);

	/**
	 * Default destructor.
	 */
	virtual ~EigenCrankNicolsonDiscretizator();
	
	/**
	 * Performs discretization process for given parameters and produces result.
	 * @return Result of discretization.
	 */
	virtual DiscretizationResult * discretize();
};

#endif