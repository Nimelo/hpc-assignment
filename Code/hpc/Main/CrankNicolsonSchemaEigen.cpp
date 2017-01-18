/**
 * @file CrankNicolsonSchemaEigen.cpp
 * @brief Implementation of methods for CrankNicolsonSchemaEigen.
 */

#include "CrankNicolsonSchemaEigen.h"
#include <Eigen>
#include <Dense>

void CrankNicolsonSchemaEigen::setLU(double a, double b, double c)
{
	int N = this->numberOfPoints;
	Eigen::MatrixXd matrix(N, N);
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			matrix(i, j) = 0;
		}
	}

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

	lu = matrix.lu();
}

void CrankNicolsonSchemaEigen::checkStabilityCondition()
{
	//TODO
}

std::vector<double>* CrankNicolsonSchemaEigen::apply(std::vector<double>* previousWave)
{
	double c = 0.25 * cfl;
	unsigned int n = previousWave->size();
	std::vector<double> q(previousWave->size());

	for (unsigned int i = 1; i < previousWave->size() - 1; i++)
	{
		q[i] = previousWave->at(i) - c * (previousWave->at(i + 1) - previousWave->at(i - 1));
	}

	q[0] = previousWave->at(0) - c * (previousWave->at(1) - previousWave->at(n - 1));
	q[n - 1] = previousWave->at(n - 1) - c * (previousWave->at(0) - previousWave->at(n - 2));

	return SolveUsingEigen(&q[0]);
}

std::vector<double> * CrankNicolsonSchemaEigen::SolveUsingEigen(double *q) 
{
	int N = this->numberOfPoints;
	Eigen::Map<Eigen::VectorXd> vector(q, N);
	Eigen::VectorXd sol = lu.solve(vector);

	return new std::vector<double>(sol.data(), sol.data() + N);
}

CrankNicolsonSchemaEigen::CrankNicolsonSchemaEigen(long coreId, long coresQuantity, unsigned int numberOfPoints, double a, double dx, double dt)
	: AbstractSchema(coreId, coresQuantity, numberOfPoints, a, dx, dt)
{
	double c = 0.25 * cfl;
	this->setLU(1.0e0, -c, c);
}

CrankNicolsonSchemaEigen::~CrankNicolsonSchemaEigen()
{
}

std::vector<double>* CrankNicolsonSchemaEigen::postApplyAction(std::vector<double>* previousWave, double t)
{
	return previousWave;
}
