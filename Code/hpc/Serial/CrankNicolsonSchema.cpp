#include "CrankNicolsonSchema.h"

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
	q[n-1] = previousWave->at(n-1) - c * (previousWave->at(0) - previousWave->at(n - 2));

	return ThomasAlgorithm_per(n, -c, 1.0e0, c, q);
}

std::vector<double> * CrankNicolsonSchema::ThomasAlgorithm_per(unsigned int N, double b, double a, double c, std::vector<double> & points)
{
	double *x = new double[N];
	int i;
	double *x1, *x2, *q2, *q;

	x1 = new double[N - 1];
	x2 = new double[N - 1];
	q2 = new double[N - 1];
	q = &points[0];

	/* Prepare secondary q */
	for (i = 0; i<N - 1; i++)
		q2[i] = 0.0;
	q2[0] = -b;
	q2[N - 2] = -c;

	ThomasAlgorithm(N - 1, b, a, c, x1, q);
	ThomasAlgorithm(N - 1, b, a, c, x2, q2);

	x[N - 1] = (q[N - 1] - c*x1[0] - b*x1[N - 2]) /
		(a + c*x2[0] + b*x2[N - 2]);

	for (i = 0; i<N - 1; i++)
		x[i] = x1[i] + x2[i] * x[N - 1];

	delete[] x1;
	delete[] x2;
	delete[] q2;
	std::vector<double> * result = new std::vector<double>(x, x + N);
	delete[] x;
	return result;
}

void CrankNicolsonSchema::ThomasAlgorithm(int N, double b, double a, double c, double *x, double *q) {
	int i;
	double *l, *u, *d, *y;

	l = new double[N];
	u = new double[N];
	d = new double[N];
	y = new double[N];

	/* LU Decomposition */
	d[0] = a;
	u[0] = c;
	for (i = 0; i<N - 2; i++) {
		l[i] = b / d[i];
		d[i + 1] = a - l[i] * u[i];
		u[i + 1] = c;
	}
	l[N - 2] = b / d[N - 2];
	d[N - 1] = a - l[N - 2] * u[N - 2];

	/* Forward Substitution [L][y] = [q] */
	y[0] = q[0];
	for (i = 1; i<N; i++)
		y[i] = q[i] - l[i - 1] * y[i - 1];

	/* Backward Substitution [U][x] = [y] */
	x[N - 1] = y[N - 1] / d[N - 1];
	for (i = N - 2; i >= 0; i--)
		x[i] = (y[i] - u[i] * x[i + 1]) / d[i];

	delete[] l;
	delete[] u;
	delete[] d;
	delete[] y;
	return;
}

CrankNicolsonSchema::CrankNicolsonSchema(double a, double dx, double dt)
	: AbstractSchema(a, dx, dt)
{
}

std::vector<double>* CrankNicolsonSchema::postApplyAction(std::vector<double>* previousWave, double t)
{
	return previousWave;
}
