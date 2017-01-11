#include "CrankNicolsonSchema.h"

void CrankNicolsonSchema::createLUDecompositionFrom(double a, double b, double c)
{
	int N = this->numberOfPoints;
	d[0] = a;
	u[0] = c;
	for (int i = 0; i < N - 2; i++) {
		l[i] = b / d[i];
		d[i + 1] = a - l[i] * u[i];
		u[i + 1] = c;
	}
	l[N - 2] = b / d[N - 2];
	d[N - 1] = a - l[N - 2] * u[N - 2];
}

void CrankNicolsonSchema::checkStabilityCondition()
{
	//TODO
}

std::vector<double>* CrankNicolsonSchema::apply(std::vector<double>* previousWave)
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

	return ForwardAndBackWardSubstition(&q[0]);
}

std::vector<double> * CrankNicolsonSchema::ForwardAndBackWardSubstition(double *q) 
{
	int N = this->numberOfPoints;

	double * y =  new double[N];
	std::vector<double> * result = new std::vector<double>(N);
	
	double * x = &(*result)[0];
	/* Forward Substitution [L][y] = [q] */
	y[0] = q[0];
	for (int i = 1; i < N; i++)
		y[i] = q[i] - l[i - 1] * y[i - 1];

	/* Backward Substitution [U][x] = [y] */
	x[N - 1] = y[N - 1] / d[N - 1];
	for (int i = N - 2; i >= 0; i--)
		x[i] = (y[i] - u[i] * x[i + 1]) / d[i];

	delete[] y;
	return result;
}

CrankNicolsonSchema::CrankNicolsonSchema(long coreId, long coresQuantity, unsigned int numberOfPoints, double a, double dx, double dt)
	: AbstractSchema(coreId, coresQuantity, numberOfPoints, a, dx, dt)
{
	this->l = new double[numberOfPoints];
	this->d = new double[numberOfPoints];
	this->u = new double[numberOfPoints];
	double c = 0.25 * cfl;
	this->createLUDecompositionFrom(1.0e0, -c, c);
}

CrankNicolsonSchema::~CrankNicolsonSchema()
{
	delete [] l;
	delete [] u;
	delete [] d;
}

std::vector<double>* CrankNicolsonSchema::postApplyAction(std::vector<double>* previousWave, double t)
{
	return previousWave;
}
