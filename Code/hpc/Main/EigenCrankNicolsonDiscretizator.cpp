/**
* @file EigenCrankNicolsonDiscretizator.cpp
* @brief Implementation of methods for EigenCrankNicolsonDiscretizator.
*/

#include <algorithm>
#include <vector>

#include "EigenCrankNicolsonDiscretizator.h"
#include "Exception.h"

std::vector<double> * EigenCrankNicolsonDiscretizator::getAnalyticalWave(double time) const
{
	double lb = this->parameters->lowerBound;
	double ub = this->parameters->upperBound;
	double dx = this->parameters->deltaX;
	double a = this->parameters->acceleration;

	unsigned int gridSize = this->parameters->meshSize;
	std::vector<double> * wave = new std::vector<double>(gridSize);

	for (unsigned int i = 0; i < (unsigned int)gridSize; i++)
	{
		wave->at(i) = this->parameters->analyticalFunction(lb + i * dx, time, a);
	}

	return wave;
}

Eigen::VectorXd EigenCrankNicolsonDiscretizator::getAnalyticalWaveEigen(double time) const
{
	double lb = this->parameters->lowerBound;
	double ub = this->parameters->upperBound;
	double dx = this->parameters->deltaX;
	double a = this->parameters->acceleration;

	unsigned int gridSize = this->parameters->meshSize;
	Eigen::VectorXd wave(gridSize);

	for (unsigned int i = 0; i < (unsigned int)gridSize; i++)
	{
		(wave)(i) = this->parameters->analyticalFunction(lb + i * dx, time, a);
	}

	return wave;
}

void EigenCrankNicolsonDiscretizator::checkStabilityCondition() const
{
}

EigenCrankNicolsonDiscretizator::EigenCrankNicolsonDiscretizator(DiscretizationParameters * parameters)
	: parameters(parameters)
{
}

EigenCrankNicolsonDiscretizator::~EigenCrankNicolsonDiscretizator()
{
	delete this->parameters;
}

DiscretizationResult * EigenCrankNicolsonDiscretizator::discretize()
{
	this->checkStabilityCondition();
	DiscretizationResult * result = new DiscretizationResult(this->parameters->lowerBound, this->parameters->upperBound, this->parameters->deltaX);
	std::sort(this->parameters->timeLevels.begin(), this->parameters->timeLevels.end());

	std::vector<double> timeLevels(this->parameters->timeLevels);

	int N = this->parameters->meshSize;
	int n = N;

	Eigen::MatrixXd matrix(N, N);

	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			matrix(i, j) = 0;
		}
	}

	double cfl = this->parameters->acceleration * this->parameters->deltaT / this->parameters->deltaX;

	double a = 1.0, b = -0.25 * cfl, c = 0.25 * cfl;
	int shift = 1;
	(matrix)(0, 0) = a;
	(matrix)(0, 1) = c;
	for (unsigned int i = 0; i < N - 2; i++)
	{
		(matrix)(shift, i) = b;
		(matrix)(shift, i + 1) = a;
		(matrix)(shift, i + 2) = c;
		shift++;
	}
	(matrix)(N - 1, N - 2) = b;
	(matrix)(N - 1, N - 1) = a;

	
	Eigen::PartialPivLU<Eigen::MatrixXd> lu = matrix.partialPivLu();
	Eigen::VectorXd q(this->parameters->meshSize);
	double time = 0.0;
	Eigen::VectorXd previousWave = getAnalyticalWaveEigen(time);
	while (timeLevels.size() > 0)
	{
		while (abs(time) < timeLevels.at(0))
		{
			try {
				c = 0.25 * cfl;

				for (unsigned int i = 1; i < previousWave.size() - 1; i++)
				{
					q[i] = (previousWave)(i) - c * ((previousWave)(i + 1) - (previousWave)(i - 1));
				}

				q[0] = (previousWave)(0) - c * ((previousWave)(1) - (previousWave)(n - 1));
				q[n - 1] = (previousWave)(n - 1) - c * ((previousWave)(0) - (previousWave)(n - 2));

				previousWave = lu.solve(q);
				time += this->parameters->deltaT;
			}
			catch (Exception & e)
			{
				throw e;
			}		
		}
		
		std::vector<double> * copy = new std::vector<double>((previousWave).data(), (previousWave).data() + N);

		result->addWaves(time - this->parameters->deltaT, copy, getAnalyticalWave(time - this->parameters->deltaT));
		timeLevels.erase(timeLevels.begin());
	}
	
	return result;
}
