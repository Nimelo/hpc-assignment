/**
 * @file CrankNicolsonParallelSchema.cpp
 * @brief Implementation of methods for CrankNicolsonParallelSchema.
 */

#include "CrankNicolsonParallelSchema.h"
#include "Constants.h"
#include "MPIWrapper.h"

void CrankNicolsonParallelSchema::setUpLUDecomposition(double a, double b, double c)
{
	int N = this->numberOfPoints;

	/* LU Decomposition */
	d[0] = coreId == Constants::ROOT_CORE ? a : (a - MPIWrapper::receiveSingleDoubleFromCore(coreId - 1, TAG_D) * c);

	u[0] = c;
	for (int i = 0; i < N - 1; i++) {
		l[i] = b / d[i];
		d[i + 1] = a - l[i] * u[i];
		u[i + 1] = c;
	}
	l[N - 1] = b / d[N - 1];

	if (coreId != coresQuantity - 1)
	{
		MPIWrapper::sendDoublesToCore(coreId + 1, TAG_D, &l[N - 1], 1);
	}
}

void CrankNicolsonParallelSchema::checkStabilityCondition()
{
	//TODO
}

std::vector<double>* CrankNicolsonParallelSchema::apply(std::vector<double>* previousWave)
{
	double c = 0.25 * cfl;
	unsigned int n = previousWave->size();
	std::vector<double> q(previousWave->size());
	double leftBound = 0, rightBound = 0;

	long sendRightCoreId = (coreId + 1) % coresQuantity;
	long recvRightCoreId = (coreId - 1 + coresQuantity) % coresQuantity;
	long sendLeftCoreId = (coreId - 1 + coresQuantity) % coresQuantity;
	long recvLeftCoreId = (coreId + 1) % coresQuantity;

	MPIWrapper::sendRecvDoubles(sendRightCoreId, 1, &previousWave->at(n - 1), TAG_RIGHT, recvRightCoreId, 1, &leftBound, TAG_RIGHT);
	MPIWrapper::sendRecvDoubles(sendLeftCoreId, 1, &previousWave->at(0), TAG_LEFT, recvLeftCoreId, 1, &rightBound, TAG_LEFT);

	for (unsigned int i = 1; i < previousWave->size() - 1; i++)
	{
		q[i] = previousWave->at(i) - c * (previousWave->at(i + 1) - previousWave->at(i - 1));
	}

	q[0] = previousWave->at(0) - c * (previousWave->at(1) - leftBound);
	q[n - 1] = previousWave->at(n - 1) - c * (rightBound - previousWave->at(n - 2));

	return this->Substitution(&(q)[0]);
}

std::vector<double> * CrankNicolsonParallelSchema::Substitution(double *q)
{
	double *y = this->ForwardSubstitution(q);
	std::vector<double> * result = this->BackwardSubstitution(y);
	delete[] y;

	return result;
}

double * CrankNicolsonParallelSchema::ForwardSubstitution(double *q)
{
	int N = this->numberOfPoints;
	double * y = new double[N];

	/* Forward Substitution [L][y] = [q] */
	if (coreId == 0)
	{
		y[0] = q[0];
	}
	else
	{
		double leftY = MPIWrapper::receiveSingleDoubleFromCore(coreId - 1, TAG_Y);
		double leftL = MPIWrapper::receiveSingleDoubleFromCore(coreId - 1, TAG_L);
		y[0] = q[0] - leftL * leftY;
	}

	for (int i = 1; i < N; i++)
		y[i] = q[i] - l[i - 1] * y[i - 1];

	if (coreId != coresQuantity - 1)
	{
		MPIWrapper::sendDoublesToCore(coreId + 1, TAG_Y, &y[N - 1], 1);
		MPIWrapper::sendDoublesToCore(coreId + 1, TAG_L, &l[N - 1], 1);
	}

	return y;
}

std::vector<double>* CrankNicolsonParallelSchema::BackwardSubstitution(double * y)
{
	int N = this->numberOfPoints;
	std::vector<double> * result = new std::vector<double>(N);
	double * x = &(*result)[0];

	/* Backward Substitution [U][x] = [y] */
	if (coreId == coresQuantity - 1)
	{
		x[N - 1] = y[N - 1] / d[N - 1];
	}
	else
	{
		double rightX = MPIWrapper::receiveSingleDoubleFromCore(coreId + 1, TAG_Z);
		x[N - 1] = (y[N - 1] - u[N - 1] * rightX) / d[N - 1];
	}

	for (int i = N - 2; i >= 0; i--)
		x[i] = (y[i] - u[i] * x[i + 1]) / d[i];

	if (coreId != 0)
	{
		MPIWrapper::sendDoublesToCore(coreId - 1, TAG_Z, &x[0], 1);
	}

	return result;
}

CrankNicolsonParallelSchema::CrankNicolsonParallelSchema(long coreId, long coresQuantity, unsigned int numberOfPoints, double a, double dx, double dt)
	: AbstractSchema(coreId, coresQuantity, numberOfPoints, a, dx, dt), TAG_D(0), TAG_L(1), TAG_LEFT(2), TAG_RIGHT(3), TAG_Y(4), TAG_Z(5)
{

	l = new double[this->numberOfPoints];
	u = new double[this->numberOfPoints];
	d = new double[this->numberOfPoints];

	double c = 0.25 * cfl;
	this->setUpLUDecomposition(1.0e0, -c, c);
}

std::vector<double>* CrankNicolsonParallelSchema::postApplyAction(std::vector<double>* previousWave, double t)
{
	return previousWave;
}

CrankNicolsonParallelSchema::~CrankNicolsonParallelSchema()
{
	delete[] l;
	delete[] u;
	delete[] d;
}
