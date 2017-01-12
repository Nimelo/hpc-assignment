/**
 * @file Constants.h
 * @brief Provides contst expresions used in application.
 */

#ifndef __H_CONSTANTS
#define __H_CONSTANTS

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
	static const long ROOT_CORE = 0;
	/*
	 * Text describing upwind explicit schema.
	 */
	static constexpr const char * UPWIND_EXPLICIT = "upwind-explicit";
	/*
	 * Text describing upwind implicit schema.
	 */
	static constexpr const char * UPWIND_IMPLICIT = "upwind-implicit";
	/*
	 * Text describing Crank-Nicolson schema.
	 */
	static constexpr const char * CRANK_NICOLSON = "crank-nicolson";
	/*
	 * Text describing parallel upwind implicit schema.
	 */
	static constexpr const char * UPWIND_EXPLICIT_PARALLEL = "upwind-explicit-parallel";
	/*
	 * Text describing parallel upwind implicit schema.
	 */
	static constexpr const char * UPWIND_IMPLICIT_PARALLEL = "upwind-implicit-parallel";
	/*
	 * Text describing parallel Crank-Nisolson schema.
	 */
	static constexpr const char * CRANK_NICOLSON_PARALLEL = "crank-nicolson-parallel";
};

#endif
