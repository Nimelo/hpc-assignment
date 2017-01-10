#ifndef __H_CONSTANTS
#define __H_CONSTANTS

class Constants
{
public:
	static const long ROOT_CORE = 0;
	static constexpr const char * UPWIND_EXPLICIT = "upwind-explicit";
	static constexpr const char * UPWIND_IMPLICIT = "upwind-implicit";
	static constexpr const char * CRANK_NICOLSON = "crank-nicolson";
	static constexpr const char * UPWIND_EXPLICIT_PARALLEL = "upwind-explicit-parallel";
	static constexpr const char * UPWIND_IMPLICIT_PARALLEL = "upwind-implicit-parallel";
	static constexpr const char * CRANK_NICOLSON_PARALLEL = "crank-nicolson-parallel";
};

#endif
