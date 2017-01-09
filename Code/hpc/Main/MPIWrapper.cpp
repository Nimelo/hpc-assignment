#include "MPIWrapper.h"

void MPIWrapper::init(int * argc, char *** argv)
{
	#ifdef MPI
		MPI_Init(argc, argv);
	#endif 
}

long MPIWrapper::getCoreId()
{
	int coreId = 0;
	#ifdef MPI
		MPI_Comm_rank(MPI_COMM_WORLD, &coreId);
	#endif
	return (long)coreId;
}

long MPIWrapper::getQuantityOfCores()
{
	int coresQuantity = 0;
	#ifdef MPI
		MPI_Comm_size(MPI_COMM_WORLD, &coresQuantity);
	#endif
	return (long)coresQuantity;
}

void MPIWrapper::finalize()
{
	#ifdef MPI
		MPI_Finalize();
	#endif
}

void MPIWrapper::sendDoublesToCore(long coreId, int tag, double * doubles, long quantity)
{
	#ifdef MPI
		MPI_Send(doubles, quantity, MPI_DOUBLE, coreId, tag, MPI_COMM_WORLD);
	#endif 
}

double MPIWrapper::receiveSingleDoubleFromCore(long coreId, int tag)
{
	double value = 0.0;
	#ifdef MPI
		MPI_Status status;
		MPI_Recv(&value, 1, MPI_DOUBLE, coreId, tag, MPI_COMM_WORLD, &status);
	#endif
	return value;
}

void MPIWrapper::receiveDoublesFromCore(long coreId, int tag, long quantity, double * storage)
{
	#ifdef MPI
		MPI_Status status;
		MPI_Recv(&storage, quantity, MPI_DOUBLE, coreId, tag, MPI_COMM_WORLD, &status);
	#endif
}
