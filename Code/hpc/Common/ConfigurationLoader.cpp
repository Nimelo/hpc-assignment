/**
 * @file ConfigurationLoader.cpp
 * @brief Implementation of methods for ConfigurationLoader.
 */
#include "ConfigurationLoader.h"
#include "ConfigurationLoadingException.h"
#include "Configuration.h"
#include "SchemasEnum.h"

#include <fstream>

ConfigurationLoader::ConfigurationLoader()
{
	TAG_LOWER_BOUND = "lowerBound";
	TAG_UPPER_BOUND = "upperBound";
	TAG_ACCELERATION = "acceleration";
	TAG_SCHEMA = "schema";
	TAG_TIME_LEVELS = "timeLevels";
	TAG_GRID_SIZE = "gridSize";
	TAG_CFL = "cfl";
}

ConfigurationLoader::~ConfigurationLoader()
{
}

ConfigurationParameter ConfigurationLoader::getConfigurationParameter(std::string key)
{
	ConfigurationParameter p;
	p.value = this->parametersMap[key];
	return p;
}

void ConfigurationLoader::loadLines(Lines lines)
{
	for (Lines::iterator it = lines.begin(); it != lines.end(); ++it)
	{
		std::string key = (*it).substr(0, (*it).find("="));
		std::string value = (*it).substr((*it).find("=") + 1);
		this->parametersMap.insert(MapPair(key, value));
	}
}

Configuration * ConfigurationLoader::loadFromFile(std::string path)
{
	try
	{
		std::ifstream ifs(path.c_str());
		std::string str;
		std::vector<std::string> lines;
		while (std::getline(ifs, str))
		{
			lines.push_back(str);
		}

		ifs.close();

		return this->loadFromLines(lines);
	}
	catch (...)
	{
		throw ConfigurationLoadingException();
	}
}

Configuration * ConfigurationLoader::loadFromLines(std::vector<std::string> lines)
{
	try
	{
		this->loadLines(lines);
		return new Configuration(
			getConfigurationParameter(TAG_LOWER_BOUND).toDouble(),
			getConfigurationParameter(TAG_UPPER_BOUND).toDouble(),
			getConfigurationParameter(TAG_ACCELERATION).toDouble(),
			getConfigurationParameter(TAG_SCHEMA).toSchema(),
			getConfigurationParameter(TAG_GRID_SIZE).toUnsignedInt(),
			getConfigurationParameter(TAG_TIME_LEVELS).toVectorOfDouble(),
			getConfigurationParameter(TAG_CFL).toDouble()
		);
	}
	catch (...)
	{
		throw ConfigurationLoadingException();
	}
}
