/**
 * @file NormSummary.h
 * @brief Declaration of methods for NormSummary.
 */
#ifndef __H_NORM_SUMMARY
#define __H_NORM_SUMMARY

#include <vector>
#include <ostream>
#include "NormsPerTimeLevel.h"

/**
 * @brief Stores information about list of NormsPerTimeLevel.
 * @see NormsPerTimeLevel
 */
class NormSummary : private std::vector<NormsPerTimeLevel>
{
	/**
	 * Simplified type for std::vector<NormsPerTimeLevel>.
	 */
	typedef std::vector<NormsPerTimeLevel> Vector;
public:

	/**
	 * Using operator [] of base class.
	 */
	using Vector::operator[];

	/**
	 * Using at method of base class.
	 */
	using Vector::at;

	/**
	 * Using size method of base class.
	 */
	using Vector::size;
	/**
	 * Using push_back method of base class.
	 */
	using Vector::push_back;

	/**
	 * Using iterator of base class.
	 */
	using Vector::iterator;

	/**
	 * Using const_iterator of base class.
	 */
	using Vector::const_iterator;

	/**
	 * Overloaded friend operator <<. 
	 * Serializes object for std::ostrem with .csv format.
	 * @param os Output stream.
	 * @param ns Norm summary object.
	 * @return Reference to Output stream given as input parameter.
	 */
	friend std::ostream & operator <<(std::ostream & os, const NormSummary & ns);
};

#endif
