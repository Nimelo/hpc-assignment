/**
 * @file WavePointsSummary.h
 * @brief Declaration of methods for WavePointsSummary.
 */

#ifndef __H_WAVE_POINTS_SUMMARY
#define __H_WAVE_POINTS_SUMMARY

#include <vector>

/**
 * @brief Structure stores analytical and numerical solutions for given time step.
 * Provides 3 methods for calculation of norms.
 * @author Mateusz Gasior
 */
struct WavePointsSummary
{
	/**
	 * Time step.
	 */
	double time;

	/**
	 * Numerical solution.
	 */
	std::vector<double> * numerical;

	/**
	 * Analytical solution.
	 */
	std::vector<double> * analytical;

	/**
	 * Overloaded constructor for explicitly given parameters.
	 * @param time Time step.
	 * @param numerical Numerical solution.
	 * @param analytical Analytical solution.
	 */
	WavePointsSummary(double time, std::vector<double> * numerical, std::vector<double> * analytical);

	/** 
	 * Default destructor.
	 */
	~WavePointsSummary();

	/**
	 * Calculates norm infinity from analytical and numerical solution.
	 * @return Calculated norm infinity.
	 */
	double errorNormInfinity() const;

	/**
	 * Calculates norm one from analytical and numerical solution.
	 * @return Calculated norm one.
	 */
	double errorNormOne() const;

	/**
	 * Calculates norm two from analytical and numerical solution.
	 * @return Calculated norm two.
	 */
	double errorNormTwo() const;
};

#endif
