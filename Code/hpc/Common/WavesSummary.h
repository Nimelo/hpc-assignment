/**
 * @file WavesSummary.h
 * @brief Declaration of methods for WaveSummary.
 */

#ifndef __H_WAVES_SUMMARY
#define __H_WAVES_SUMMARY

#include <vector>
#include <ostream>

#include "WavePointsSummary.h"

/**
 * @brief Stores information about list of WavePointsSummary.
 * @see WavePointsSummary
 * @see std::vector
 * Provides all functionality of base class with additional of serialization to .csv format.
 * @author Mateusz Gasior
 */
class WavesSummary : public std::vector<WavePointsSummary *>
{
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
public:

	/**
	 * Overloaded constructor for explicitly given parameters.
	 * @param lowerBound Lower bound.
	 * @param upperBound Upper bound.
	 * @param deltaX Delta x.
	 */
	WavesSummary(double lowerBound, double upperBound, double deltaX);

	/**
	 * Default destructor.
	 */
	~WavesSummary();

	/**
	 * Overloaded friend operator <<.
	 * Serializes object for std::ostrem with .csv format.
	 * @param os Output stream.
	 * @param ws Waves Summary object.
	 * @return Reference to Output stream given as input parameter.
	 */
	friend std::ostream & operator <<(std::ostream & os, const WavesSummary & ws);
};

#endif
