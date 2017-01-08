#include <iostream>
#include <fstream>

#include "ConfigurationLoader.h"
#include "Configuration.h"

#include "AnalyticalFunctions.h"
#include "DefaultSchemasResolver.h"

#include "DiscretizationParameters.h"
#include "Discretizator.h"

#include "DiscretizationResult.h"
#include "Exception.h"
#include "ConfigurationLoadingException.h"
#include "DiscretizationParameters.h"
#include "DefaultSchemasResolver.h"
#include "WavePointsSummary.h"
#include "NormSummary.h"

#define PARAMETER_COUNT 4

#define CONFIGURATION_FILE_INDEX 1
#define WAVE_FILE_INDEX 2
#define NORM_FILE_INDEX 3

/**
* @brief Main entry point for application.
* Requires 4 additional parameters to run:
*			- Name of configuration file.
*			- Name for output wave file.
*			- Name for output norm file.
* @param argc Parameter count.
* @param argv Array of arguments.
* @return int Zero if program executed correctly.
*/
int main(int argc, char * argv[])
{
	try 
	{
		if (argc != PARAMETER_COUNT)
		{
			std::cout << "Invalid amount of parameters." << std::endl;
			return -1;
		}

		char * configurationFile = argv[CONFIGURATION_FILE_INDEX];
		char * wavesFile = argv[WAVE_FILE_INDEX];
		char * normsFile = argv[NORM_FILE_INDEX];

		ConfigurationLoader configurationLoader;
		Configuration * configuration = configurationLoader.loadFromFile(configurationFile);

		double dx = (configuration->upperBound - configuration->lowerBound) / configuration->numberOfPoints;
		double dt = (configuration->cfl * dx) / configuration->acceleration;

		DefaultSchemasResolver * schemaResolver = new DefaultSchemasResolver();

		DiscretizationParameters * discretizationParameters = new DiscretizationParameters(
			configuration->lowerBound,
			configuration->upperBound,
			configuration->acceleration,
			(long)configuration->numberOfPoints,
			AnalyticalFunctions::expFunction,
			schemaResolver->resolve(configuration->schema, configuration->acceleration, dx, dt),
			configuration->timeLevels,
			dt,
			dx
		);

		Discretizator discretizator(discretizationParameters);

		DiscretizationResult * result = discretizator.discretize();

		std::fstream ws;
		ws.open(wavesFile, std::fstream::out | std::fstream::trunc);
		WavesSummary * pointsAtTimeT = result->getValuesAtTimeT();
		ws << *pointsAtTimeT;
		ws.close();

		std::fstream ns;
		ns.open(normsFile, std::fstream::out | std::fstream::trunc);
		NormSummary * norms = result->getNorms();
		std::cout << *norms;
		ns << *norms;
		ns.close();

		delete schemaResolver;
		delete result;
		delete configuration;
		delete norms;
	}
	catch (...)
	{
		std::cout << "Exception" << std::endl;
	}

	return 0;
}