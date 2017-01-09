#include <mpi.h>
#include <cmath>
#include <vector>
#include <iostream>

double analyticalSolution(double a, double x, double t);
unsigned int getFragmentation(int coreId, int coresQuantity, unsigned int jobSize);

double getLowerBound(int coreId, int coresQuantity);
void sendUpperBound(int coreId, int coresQuantity, double value);

void initializeArray(double * array, double lowerBound, double acceleration, unsigned int fragmentation, double dx);

void normCalculateNorms(double * finalSolution, unsigned int numberOfPoints, double lowerBound, double acceleration, double dx, double time);

int main(int argc, char * argv[])
{
	int coreId;
	int coresQuantity;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &coreId);
	MPI_Comm_size(MPI_COMM_WORLD, &coresQuantity);

	double lowerBound = -50;
	double upperBound = 50;
	double acceleration = 1.75;
	unsigned int numberOfPoints = 6;
	double _timeSteps[2] = {5.0, 10.0};
	std::vector<double> timeSteps(_timeSteps, _timeSteps + 2);
	double cfl = 0.1;
	double dx = (upperBound - lowerBound) / numberOfPoints;
	double dt = (cfl * dx) / acceleration;

	double leftBound = 0;
	unsigned int fragmentation = getFragmentation(coreId, coresQuantity, numberOfPoints);

	double currentTime = 0.0;
	double * oldSolution = new double [fragmentation];
	double * newSolution = new double [fragmentation];
	initializeArray(oldSolution, lowerBound + coreId * dx * (numberOfPoints / coresQuantity), acceleration, fragmentation, dx);

	//for (unsigned int i = 0; i < timeSteps.size(); i++) {
		while(timeSteps[0] > currentTime) {
			leftBound = getLowerBound(coreId, coresQuantity);

			newSolution[0] = oldSolution[0] - cfl * (oldSolution[0] - leftBound);
			for (unsigned int space = 1; space < fragmentation; space++) {
				newSolution[space] = oldSolution[space] - cfl * (oldSolution[space] - oldSolution[space - 1]);
			}

			for (unsigned int i = 0; i < fragmentation; i++) {
				oldSolution[i] = newSolution[i];
			}

			sendUpperBound(coreId, coresQuantity, oldSolution[fragmentation - 1]);

			currentTime += dt;
		}
	//}
	std::cout << "CoreId: " << coreId << std::endl;

	if(coreId == 0)
	{
		double * finalSolution = new double [numberOfPoints];
		double * index = finalSolution;

		for (unsigned int i = 0; i < fragmentation; i++) {
			finalSolution[i] = oldSolution[i];
		}

		for (unsigned int i = 1; i < coresQuantity; i++) {
			MPI_Status status;
			unsigned int fragmentationForI = getFragmentation(i, coresQuantity, numberOfPoints);
			MPI_Recv(index, fragmentationForI, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, &status);
			index += fragmentationForI;
		}

		normCalculateNorms(finalSolution, numberOfPoints, lowerBound, acceleration, dx, currentTime - dt);
		delete [] finalSolution;
	}else {
		MPI_Send(oldSolution, fragmentation, MPI_DOUBLE, 0,  1, MPI_COMM_WORLD);
	}

	delete [] oldSolution;
	delete [] newSolution;

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}

void normCalculateNorms(double * finalSolution, unsigned int numberOfPoints, double lowerBound, double acceleration, double dx, double time)
{
	double norm = 0.0;
	for (unsigned int i = 0; i < numberOfPoints; i++) {
		norm += fabs(analyticalSolution(acceleration, lowerBound + i * dx, time) - finalSolution[i]);
	}

	std::cout << "The norm 1 is equal to :" << norm / numberOfPoints << std::endl;
}

void initializeArray(double * array, double lowerBound, double acceleration, unsigned int fragmentation, double dx)
{
		for (unsigned int i = 0; i < fragmentation; i++) {
			array[i] = analyticalSolution(acceleration, lowerBound + i * dx, 0.0);
		}
}

double analyticalSolution(double a, double x, double t)
{
	return 0.5 * exp(-(x - a * t) * (x - a * t));
}

unsigned int getFragmentation(int coreId, int coresQuantity, unsigned int jobSize)
{
		if(coresQuantity == 1)
			return jobSize;
		else if(jobSize % coresQuantity == 0)
			return jobSize / coresQuantity;
		else
		{
			if(coreId == coresQuantity - 1)
				return jobSize / coresQuantity + jobSize % coresQuantity;
			else
				return jobSize / coresQuantity;
		}
}

void sendUpperBound(int coreId, int coresQuantity, double value)
{
	if(coreId != coresQuantity - 1)
	{
				std::cout << "sendUpperBound by " << coreId << std::endl;
				MPI_Send(&value, 1, MPI_DOUBLE, coreId + 1,  0, MPI_COMM_WORLD);
	}
}

double getLowerBound(int coreId, int coresQuantity)
{
	std::cout << "getLowerBound by " << coreId << std::endl;
	if (coreId == 0) {
		return 0;
	} else {
		MPI_Status status;
		double a;
		MPI_Recv(&a, 1, MPI_DOUBLE, coreId - 1, 0, MPI_COMM_WORLD, &status);
		return a;
	}
}
