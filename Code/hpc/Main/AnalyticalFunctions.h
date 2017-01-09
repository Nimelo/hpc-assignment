/**
 * @file AnalyticalFunctions.h
 * @brief Declaration of methods for AnalyticalFunctions.
 */

#ifndef __H_ANALYTICAL_FUNCTIONS
#define __H_ANALYTICAL_FUNCTIONS

/**
 * @brief Contains implementations of analytical function that are used in discretization process.
 * @author Mateusz Gasior
 */
class AnalyticalFunctions
{
public:

	/**
	 * Function that uses exponential mathematical function.
	 * \f$ f(x,t) = 0.5 * exp (-(x - at)^2) \f$
	 * @param x Space dimension.
	 * @param t Time dimension.
	 * @param a Acceleration.
	 * @return Calculated value.
	 */
	 double static expFunction(double x, double t, double a);
};

#endif
