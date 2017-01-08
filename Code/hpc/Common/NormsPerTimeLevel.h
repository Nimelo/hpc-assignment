/**
 * @file NormsPerTimeLevel.h
 * @brief Declaration of methods for NormsPerTimeLevel.
 */

#ifndef __H_NORMS_PER_TIME_LEVEL
#define __H_NORMS_PER_TIME_LEVEL

/**
 * @brief Structure used for storing values of the norms for given time level.
 * @author Mateusz Gasior
 */
struct NormsPerTimeLevel
{
	/**
	 * Time level.
	 */
	double time;

	/**
	 * Calculated norm infinity.
	 */
	double normInfinity;

	/**
	 * Calculated norm one.
	 */
	double normOne;

	/**
	 * Calculated norm two.
	 */
	double normTwo;


	/**
	 * Constructor for explicitly given parameters.
	 * @param time Time level.
	 * @param normInfinity Norm inifnity.
	 * @param normOne Norm one.
	 * @param normTwo Norm two.
	 */
	NormsPerTimeLevel(double time, double normInfinity, double normOne, double normTwo)
		: time(time), normInfinity(normInfinity), normOne(normOne), normTwo(normTwo)
	{

	}
};

#endif
