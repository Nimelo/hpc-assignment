/**
 * @file Constants.h
 * @brief Provides contst expresions used in application.
 */

#ifndef __H_CONSTANTS
#define __H_CONSTANTS

#include <string>

/**
* @brief Provides const expresions used in across applicaiton.
* @author Mateusz Gasior
*/
class Constants
{
public:
	/*
	 * Id of main core.
	 */
	static const long ROOT_CORE;
	/*
	 * Text describing upwind explicit schema.
	 */
	static const std::string UPWIND_EXPLICIT;
	/*
	 * Text describing upwind implicit schema.
	 */
	static const std::string UPWIND_IMPLICIT;
	/*
	 * Text describing Crank-Nicolson schema.
	 */
	static const std::string CRANK_NICOLSON;
	/*
	 * Text describing parallel upwind implicit schema.
	 */
	static const std::string UPWIND_EXPLICIT_PARALLEL;
	/*
	 * Text describing parallel upwind implicit schema.
	 */
	static const std::string UPWIND_IMPLICIT_PARALLEL;
	/*
	 * Text describing parallel Crank-Nisolson schema.
	 */
	static const std::string CRANK_NICOLSON_PARALLEL;
};

#endif
