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
	MPIWrapper::sendRecvDoubles(sendRightCoreId, 1, &previousWave->at(n - 1), TAG_RIGHT, recvRightCoreId, 1, &leftBound, TAG_RIGHT);
	MPIWrapper::sendRecvDoubles(sendLeftCoreId, 1, &previousWave->at(0), TAG_LEFT, recvLeftCoreId, 1, &rightBound, TAG_LEFT);

	//previousWave->at(0) = leftBound;
	//previousWave->at(n - 1) = rightBound;
	/*for (size_t i = 0; i < coresQuantity; i++) {
		if (coreId == i) {
			std::cout << "coreId " << coreId <<std::endl;
			std::cout << "left " << leftBound <<std::endl;
			std::cout << "right " << rightBound <<std::endl;
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}*/
	for (unsigned int i = 1; i < previousWave->size() - 1; i++)
	{
		q[i] = previousWave->at(i) - c * (previousWave->at(i + 1) - previousWave->at(i - 1));
	}

	q[0] = previousWave->at(0) - c * (previousWave->at(1) - leftBound/*previousWave->at(n - 1)*/);
	q[n - 1] = previousWave->at(n - 1) - c * (rightBound/*previousWave->at(0)*/ - previousWave->at(n - 2));
	std::vector<double> * result = new std::vector<double>(n);
	/*for (size_t i = 0; i < coresQuantity; i++) {
		if (coreId == i) {
			std::cout << "coreId " << coreId <<std::endl;
			for (size_t j = 0; j < n; j++) {
				std::cout << q[j] << std::endl;
			}
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}*/
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
		u[0] = c;
		for (i = 0; i < N - 1; i++) {
			l[i] = b / d[i];
			d[i + 1] = a - l[i] * u[i];
			u[i + 1] = c;
		}
		l[N - 1] = b / d[N - 1];
	}
	else if (coreId == coresQuantity - 1)
	{
		d[0] = a - MPIWrapper::receiveSingleDoubleFromCore(coreId - 1, TAG_D) * c;
		u[0] = c;
		for (i = 0; i < N - 1; i++) {
			l[i] = b / d[i];
			d[i + 1] = a - l[i] * u[i];
			u[i + 1] = c;
		}
		l[N - 1] = b / d[N - 1];
		//d[N - 1] = a - l[N - 2] * u[N - 2];
	}
	else
	{
		d[0] = a - MPIWrapper::receiveSingleDoubleFromCore(coreId - 1, TAG_D) * c;
		u[0] = c;
		for (i = 0; i < N - 1; i++) {
			l[i] = b / d[i];
			d[i + 1] = a - l[i] * u[i];
			u[i + 1] = c;
		}
		l[N - 1] = b / d[N - 1];
	}

	/*for (size_t i = 0; i < coresQuantity; i++) {
		if (coreId == i) {
			std::cout << "coreId " << coreId <<std::endl;
			std::cout << "l d u\n";
			for (size_t j = 0; j < N; j++) {
				std::cout << l[j] << " " << d[j] << " " << u[j] << std::endl;
			}
		}
		//MPI_Barrier(MPI_COMM_WORLD);
	}*/
	// send
	if (coreId != coresQuantity - 1)
	{
		MPIWrapper::sendDoublesToCore(coreId + 1, TAG_D, &l[N - 1], 1);
	}

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

	//y[0] = q[0]; // get
	for (i = 1; i < N; i++)
		y[i] = q[i] - l[i - 1] * y[i - 1];
/*
		for (size_t i = 0; i < coresQuantity; i++) {
			if (coreId == i) {
				std::cout << "coreId " << coreId <<std::endl;
				std::cout << "y\n";
				for (size_t j = 0; j < N; j++) {
					std::cout << y[j] << std::endl;
				}
			}
			//MPI_Barrier(MPI_COMM_WORLD);
		}*/
	// send
	if (coreId != coresQuantity - 1)
	{
		MPIWrapper::sendDoublesToCore(coreId + 1, TAG_Y, &y[N - 1], 1);
		MPIWrapper::sendDoublesToCore(coreId + 1, TAG_L, &l[N - 1], 1);
	}

	/* Backward Substitution [U][x] = [y] */
	if (coreId == coresQuantity - 1)
	{
		x[N - 1] = y[N - 1] / d[N - 1];
	}
	else
	{
		double rightX = MPIWrapper::receiveSingleDoubleFromCore(coreId + 1, TAG_Z);
		x[N - 1] = (y[N-1] - u[N-1] * rightX)/d[N-1];
	}
	//x[N - 1] = y[N - 1] / d[N - 1]; // get
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

CrankNicolsonParallelSchema::CrankNicolsonParallelSchema(long coreId, long coresQuantity, unsigned int numberOfPoints, double a, double dx, double dt)
	: AbstractSchema(coreId, coresQuantity, numberOfPoints, a, dx, dt)
{
}

std::vector<double>* CrankNicolsonParallelSchema::postApplyAction(std::vector<double>* previousWave, double t)
{
	return previousWave;
}
