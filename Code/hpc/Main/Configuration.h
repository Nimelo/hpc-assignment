/**
 * @file Configuration.h
 * @brief Declaration of methods for Configuration.
 */
#ifndef __H_CONFIGURATION
#define __H_CONFIGURATION

#include <vector>
#include <string>


/**
 * @brief Stores information about all parameters used during discretization process, such as types and numeric values.
 * @author Mateusz Gasior
 */
struct Configuration
{	
	/**
	 * Lower boundary.
	 */
	double lowerBound;

	/**
	 * Upper boundary.
	 */
	double upperBound;

	/**
	 * Acceleration for advection function.
	 */
	double acceleration;

	/**
	 * Schema enumerator that is used in disretization process.
	 * @see SchemasEnum
	 */
	std::string schema;

	/**
	 * Mesh size (grid size).
	 */
	unsigned int numberOfPoints;

	/**
	 * Time levels for which there should be performed additional actions, such as calculation of norms and printing to file.
	 */
	std::vector<double> timeLevels;

	/**
	* Courant-Friedrich-Lewy (CFL) number.
	*/
	double cfl;

	/**
	* Overloaded constructor for Configuration with specified delta t.
	* @param lowerBound Lower boundary.
	* @param upperBound Upper boundary.
	* @param acceleration Acceleration.
	* @param schema Schema enumerator.
	* @param numberOfPoints Mesh size.
	* @param timeLevels Time levels.
	* @param cfl CFL number.
	*/
	Configuration(double lowerBound, double upperBound, double acceleration, std::string schema, unsigned int numberOfPoints,
		std::vector<double> timeLevels, double cfl);
};
#endif
