#include "ParallelExplicitDiscretizator.h"

std::vector<double>* ParallelExplicitDiscretizator::getAnalyticalWave(double time)
{
	return nullptr;
}

void ParallelExplicitDiscretizator::checkStabilityCondition()
{
}

DiscretizationResult * ParallelExplicitDiscretizator::discretize()
{
	DiscretizationResult * result;

	if(coreId == MAIN_CORE_ID)
	{
		result = new DiscretizationResult(this->parameters->lowerBound, this->parameters->upperBound, this->parameters->deltaX);
	}

	this->checkStabilityCondition();
	std::sort(this->parameters->timeLevels.begin(), this->parameters->timeLevels.end());

	double currentTime = 0.0;
	std::vector<double> * oldSolution = getAnalyticalWave(currentTime);

	while(timeLevels.size() > 0)
	{
		while(abs(currentTime) < timeLevels.at(0))
		{
			//RECEIVE SOMEHTING ()
			//SEND IF CAN IN TIME CURRENT TIME
			try {
				std::vector<double> * newSolution = this->parameters->schema->apply(previousWave);
				delete oldSolution;
				oldSolution = newSolution;
				time += this->parameters->deltaT;
			}
			catch (Exception & e)
			{
				delete oldSolution;
				throw e;
			}
		}

		if (coreId == MAIN_CORE_ID)
		{
			gatherPartialResult(result, time - this->parameters->deltaT);
		}
		else
		{
			sendPartialResult();
		}
		timeLevels.erase(timeLevels.begin());
	}

	delete oldSolution;
	return result;
}
