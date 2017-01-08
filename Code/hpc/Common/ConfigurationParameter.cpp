/**
* @file ConfigurationParameter.cpp
* @brief Implementation of methods for ConfigurationParameter.
*/
#include "ConfigurationParameter.h"

double ConfigurationParameter::toDouble()
{
	std::stringstream ss(value);
	double convertedValue;
	if (std::stringstream(value) >> convertedValue)
		return convertedValue;
	else
		throw std::runtime_error("Conversion failed");
}

unsigned int ConfigurationParameter::toUnsignedInt()
{
	std::stringstream ss(value);
	unsigned int convertedValue;
	if (std::stringstream(value) >> convertedValue)
		return convertedValue;
	else
		throw std::runtime_error("Conversion failed");
}

std::vector<double> ConfigurationParameter::toVectorOfDouble()
{
	std::stringstream ss(value);
	std::vector<double> returnValue;
	std::string token;
	double convertedValue;
	while (std::getline(ss, token, ',')) {
		if (std::stringstream(token) >> convertedValue)
			returnValue.push_back(convertedValue);
		else
			throw std::runtime_error("Conversion failed");
	}

	return returnValue;
}

SchemasEnum ConfigurationParameter::toSchema()
{
	if (value == "upwind-implicit")
	{
		return UPWIND_IMPLICIT;
	}
	else if (value == "upwind-explicit")
	{
		return UPWIND_EXPLICIT;
	}
	else if (value == "crank-nicolson")
	{
		return CRANK_NICLOSON;
	}
	else
		throw std::runtime_error("Conversion failed");
}

bool ConfigurationParameter::toBool()
{
	if (value == "true" || value == "1")
		return true;
	else if (value == "false" || value == "0")
		return false;
	else throw std::runtime_error("Conversion failed");
}
