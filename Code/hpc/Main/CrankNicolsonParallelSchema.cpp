#include "CrankNicolsonParallelSchema.h"
#include "Constants.h"
#include "MPIWrapper.h"

void CrankNicolsonParallelSchema::sendLeftBound(double value)
{
	if (coreId != Constants::ROOT_CORE)
	{
		MPIWrapper::sendDoublesToCore(coreId - 1, TAG_LEFT, &value, 1);
	}
}

double CrankNicolsonParallelSchema::recvLeftBound(double bound)
{
	if (coreId == Constants::ROOT_CORE)
	{
		return bound;
	}
	else
	{
		return MPIWrapper::receiveSingleDoubleFromCore(coreId - 1, TAG_RIGHT);
	}
}

void CrankNicolsonParallelSchema::sendRightBound(double value)
{
	if (coreId != coresQuantity - 1)
	{
		MPIWrapper::sendDoublesToCore(coreId + 1, TAG_RIGHT, &value, 1);
	}
}

double CrankNicolsonParallelSchema::recvRightBound(double bound)
{
	if (coreId == coresQuantity - 1)
	{
		return bound;
	}
	else
	{
		return MPIWrapper::receiveSingleDoubleFromCore(coreId + 1, TAG_LEFT);
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
	MPIWrapper::sendRecvDoubles(sendRightCoreId, 1, &previousWave->at(n - 1), TAG_RIGHT, recvRightCoreId, 1, &rightBound, TAG_RIGHT);
	MPIWrapper::sendRecvDoubles(sendLeftCoreId, 1, &previousWave->at(0), TAG_LEFT, recvLeftCoreId, 1, &leftBound, TAG_LEFT);

	//previousWave->at(0) = leftBound;
	//previousWave->at(n - 1) = rightBound;

	for (unsigned int i = 1; i < previousWave->size() - 1; i++)
	{
		q[i] = previousWave->at(i) - c * (previousWave->at(i + 1) - previousWave->at(i - 1));
	}

	q[0] = previousWave->at(0) - c * (previousWave->at(1) - leftBound/*previousWave->at(n - 1)*/);
	q[n - 1] = previousWave->at(n - 1) - c * (rightBound/*previousWave->at(0)*/ - previousWave->at(n - 2));
	std::vector<double> * result = new std::vector<double>(n);
	ThomasAlgorithm(n, -c, 1.0e0, c, &(*result)[0], &(q)[0]);
	return result;
}

void CrankNicolsonParallelSchema::ThomasAlgorithm(int N, double b, double a, double c, double *x, double *q) {
	int i;
	double *l, *u, *d, *y;

	l = new double[N];
	u = new double[N];
	d = new double[N];
	y = new double[N];

	/* LU Decomposition */
	if (coreId == 0)
	{
		d[0] = a;
	}
	else 
	{
		d[0] = MPIWrapper::receiveSingleDoubleFromCore(coreId - 1, TAG_D);
	}

	//d[0] = a; // get
	u[0] = c;
	for (i = 0; i < N - 2; i++) {
		l[i] = b / d[i];
		d[i + 1] = a - l[i] * u[i];
		u[i + 1] = c;
	}
	l[N - 2] = b / d[N - 2];
	d[N - 1] = a - l[N - 2] * u[N - 2];

	// send 
	if (coreId != coresQuantity - 1)
	{
		MPIWrapper::sendDoublesToCore(coreId + 1, TAG_D, &d[N - 1], 1);
	}

	/* Forward Substitution [L][y] = [q] */
	if (coreId == 0)
	{
		y[0] = q[0];
	}
	else
	{
		y[0] = MPIWrapper::receiveSingleDoubleFromCore(coreId - 1, TAG_Y);
	}

	//y[0] = q[0]; // get
	for (i = 1; i < N; i++)
		y[i] = q[i] - l[i - 1] * y[i - 1];

	// send 
	if (coreId != coresQuantity - 1)
	{
		MPIWrapper::sendDoublesToCore(coreId + 1, TAG_Y, &y[N - 1], 1);
	}

	/* Backward Substitution [U][x] = [y] */
	if (coreId == coresQuantity - 1)
	{
		x[N - 1] = y[N - 1] / d[N - 1];
	}
	else
	{
		x[N - 1] = MPIWrapper::receiveSingleDoubleFromCore(coreId + 1, TAG_Z);
	}
	x[N - 1] = y[N - 1] / d[N - 1]; // get
	for (i = N - 2; i >= 0; i--)
		x[i] = (y[i] - u[i] * x[i + 1]) / d[i];

	// send 
	if (coreId != 0)
	{
		MPIWrapper::sendDoublesToCore(coreId - 1, TAG_Z, &x[0], 1);
	}

	delete[] l;
	delete[] u;
	delete[] d;
	delete[] y;
	return;
}

CrankNicolsonParallelSchema::CrankNicolsonParallelSchema(long coreId, long coresQuantity, double a, double dx, double dt)
	: AbstractSchema(coreId, coresQuantity, a, dx, dt)
{
}

std::vector<double>* CrankNicolsonParallelSchema::postApplyAction(std::vector<double>* previousWave, double t)
{
	return previousWave;
}
