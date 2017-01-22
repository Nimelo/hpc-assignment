/**
 * @file DiscretizationResult.h
 * @brief Declaration of methods for DiscretizationResult.
 */

#ifndef __H_DISCRETIZATION_RESULT
#define __H_DISCRETIZATION_RESULT

#include <vector>
#include <ostream>

#include "WavesSummary.h"
#include "WavePointsSummary.h"
#include "NormSummary.h"

/**
 * @brief Result of discretization. 
 * Stores and provides all neccessary informations produced during discretization proceess.
 */
class DiscretizationResult
{
	/**
	 * Siplified std::vector<WavePointsSummary *> type.
	 */
	typedef std::vector<WavePointsSummary *> Vector;
private:

	/**
	 * Lower bound.
	 */
	double lowerBound;

	/**
	 * Upper bound.
	 */
	double upperBound;

	/**
	 * Delta x.
	 */
	double deltaX;

	/**
	 * Summaries for all the waves.
	 */
	WavesSummary * summaries;

public:
	double communicationTime;
	/**
	 * Overloaded constructor for explicitly given parameters.
	 * @param lowerBound Lower bound.
	 * @param upperBound Upper bound.
	 * @param deltaX Delta x.
	 */
	DiscretizationResult(double lowerBound, double upperBound, double deltaX);

	/**
	 * Default destructor.
	 */
	~DiscretizationResult();

	/**
	 * Returns summary of the waves for all time levels.
	 * @return Summary of the waves.
	 */
	WavesSummary * getValuesAtTimeT() const;

	/**
	 * Returns norms for all time levels.
	 * @return Norms for all time levels.
	 */
	NormSummary * getNorms();

	/**
	 * Adds new entry for wave summaries.
	 * @param time Time level.
	 * @param numerical Numerical solution for given time level.
	 * @param analytical Analytical solution for given time level.
	 */
	void addWaves(double time, std::vector<double> * numerical, std::vector<double> * analytical);
};

#endif
