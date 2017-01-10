#include <iostream>
#include <fstream>

#include "ConfigurationLoader.h"
#include "Configuration.h"

#include "DiscretizatorsFactory.h"
#include "DiscretizationResult.h"
#include "Exception.h"
#include "ConfigurationLoadingException.h"
#define MPI
#include "MPIWrapper.h"

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

		MPIWrapper::init(&argc, &argv);
		long coreId = MPIWrapper::getCoreId();
		long coresQuantity = MPIWrapper::getQuantityOfCores();
		std::cout << "coreId: " <<coreId << std::endl;
		std::cout << "coresQuantity: " << coresQuantity << std::endl;
		char * configurationFile = argv[CONFIGURATION_FILE_INDEX];
		char * wavesFile = argv[WAVE_FILE_INDEX];
		char * normsFile = argv[NORM_FILE_INDEX];

		ConfigurationLoader configurationLoader;
		Configuration * configuration = configurationLoader.loadFromFile(configurationFile);

		DiscretizatorsFactory discretizatorsFactory;
		Discretizator * discretizator = discretizatorsFactory.manufacture(configuration, coreId, coresQuantity);

		DiscretizationResult * result = discretizator->discretize();

		if(coreId == 0)
		{
			//TODO: ResultSaver
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
			delete result;
			delete norms;
		}
		
		delete discretizator;
		delete configuration;
	}
	catch (...)
	{
		std::cout << "Exception" << std::endl;
	}

	MPIWrapper::finalize();
	return 0;
}
