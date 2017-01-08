/**
 * @file ConfigurationLoader.h
 * @brief Declaration of methods for ConfigurationLoader.
 */
#ifndef __H_CONFIGURATION_LOADER
#define __H_CONFIGURATION_LOADER

#include <vector>
#include <map>
#include <utility>
#include <string>

#include "Configuration.h"
#include "ConfigurationParameter.h"

/**
 * @brief ConfigurationLoader is responsible for creating an Configuration from a file or vector of parameters.
 * @see Configuration
 * @author Mateusz Gasior
 */
class ConfigurationLoader
{
	/**
	 * Simplified type for std::vector<std::string>.
	 */
	typedef std::vector<std::string> Lines;

	/**
	 * Simplified type for std::map<std::string, std::string>.
	 */
	typedef std::map<std::string, std::string> Map;

	/**
	 * Simplified type for std::pair<std::string, std::string>.
	 */
	typedef std::pair<std::string, std::string> MapPair;
private:
	/**
	 * Lower boundary tag/key for configuration.
	 */
	std::string TAG_LOWER_BOUND;

	/**
	 * Upper boundary tag/key for configuration.
	 */
	std::string TAG_UPPER_BOUND;

	/**
	 * Acceleration tag/key for configuration.
	 */
	std::string TAG_ACCELERATION;
	
	/**
	 * Analytical function tag/key for configuration.
	 */
	std::string TAG_ANALYTICAL_FUNCTION;
	
	/**
	 * Schema tag/key for configuration.
	 */
	std::string TAG_SCHEMA;

	/**
	 * Time levels tag/key for configuration.
	 */
	std::string TAG_TIME_LEVELS;

	/**
	 * Grid size (mesh size) tag/key for configuration.
	 */
	std::string TAG_GRID_SIZE;
	
	/**
	 * CFL tag/key for configuration.
	 */
	std::string TAG_CFL;

	/**
	 * Map of the parameters.
	 * Keys and values are temporary stored as strings.
	 */
	Map parametersMap;

	/**
	 * Searches for value in parametersMap for given key and returns value as ConfigurationParameter.
	 * @see ConfigurationParameter
	 * @param key string to search for.
	 * @return ConfigurationParameter parameter corresponding to given key.
	 */
	ConfigurationParameter getConfigurationParameter(std::string key);

	/**
	 * Loades line into parametersMap. 
	 * Clears parametersMap before adding new elements.
	 * @param lines parameters stored in a vector. Each value is separated from a key by a single '=' character.
	 */
	void loadLines(Lines lines);
public:

	/**
	 * Default constructor.
	 */
	ConfigurationLoader();

	/**
	 * Default destructor.
	 */
	~ConfigurationLoader();

	/**
	 * Produces Configuration stored in a file of given path.
	 * @see Configuration
	 * @param path Path to the file with configuration.
	 * @return Configuration Configuration for discretization.
	 * @throws ConfigurationLoadingException if configuration is invalid or file doesn't exist.
	 */
	Configuration * loadFromFile(std::string path);

	/**
	* Produces Configuration stored in a vector of parameters.
	* @see Configuration
	* @param lines Vector of parameters.
	* @return Configuration Configuration for discretization.
	* @throws ConfigurationLoadingException if configuration is invalid.
	*/
	Configuration * loadFromLines(std::vector<std::string> lines);
};
#endif
