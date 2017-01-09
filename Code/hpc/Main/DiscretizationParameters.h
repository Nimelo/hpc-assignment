/**
 * @file DiscretizationParameters.h
 * @brief Declaration of methods for DiscretizationParameters.
 */
#ifndef __H_DISCRETIZATION_PARAMETERS
#define __H_DISCRETIZATION_PARAMETERS

#include <vector>

#include "AbstractSchema.h"

/**
 * @brief Stores values needed to perform discretization.
 */
struct DiscretizationParameters
{
	/**
	 * Lower bound.
	 */
	double lowerBound;

	/**	
	* Upper bound.
	*/
	double upperBound;

	/**
	* Acceleration.
	*/
	double acceleration;

	/**
	 * Analytical function.
	 */
	double (*analyticalFunction) (double, double, double);

	/**
	 * Schema.
	 */
	AbstractSchema * schema;

	/**
	 * Mesh size (grid size).
	 */
	unsigned int meshSize;

	/**
	 * Time levels.
	 */
	std::vector<double> timeLevels;

	/**
	 * Delta x.
     */
	double deltaX;

	/**
	* Delta x.
	*/
	double deltaT;

	/**
	 * Overloaded constructor for explicitly given parameters.
	 * @param lowerBound Lower bound.
	 * @param upperBound Upper bound.
	 * @param acceleration Acceleration.
	 * @param analyticalFunction Analytical function.
	 * @param schema Schema.
	 * @param meshSize Mesh size (grid size).
	 * @param timeLevels Time levels.
	 * @param dt Delta t.
	 * @param dx Delta x.
	 */
	DiscretizationParameters(double lowerBound, double upperBound, double acceleration,
		unsigned int meshSize, double(*analyticalFunction) (double, double, double), 
		AbstractSchema * schema, std::vector<double> timeLevels,
		double dt, double dx);

	/**
	 * Default destructor.
	 */
	~DiscretizationParameters();
};

#endif
