/**
 * @file ConfigurationLoadingException.h
 * @brief Declaration of methods for ConfigurationLoadingException.
 */

#ifndef __H_CONFIGURATION_LOADING_EXCEPTION
#define __H_CONFIGURATION_LOADING_EXCEPTION

#include "Exception.h"

/**
 * @brief Exception used when there is a problem with loading a confiuration.
 * @see Configuration
 * @see ConfigurationLoader
 * @see Exception
 * @author Mateusz Gasior
 */
class ConfigurationLoadingException : public Exception
{
};
#endif
