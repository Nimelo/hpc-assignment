/**
 * @file StabilityConditionException.h
 * @brief Declaration of methods for StabilityConditionException.
 */

#ifndef __H_STABILITY_CONDITION_EXCEPTION
#define __H_STABILITY_CONDITION_EXCEPTION

#include "Exception.h"

/**
 * @brief Used when schema becomes unstable.
 * @see AbstractSchema
 * @see Exception
 * @author Mateusz Gasior
 */
class StabilityConditionException : public Exception
{
};

#endif
