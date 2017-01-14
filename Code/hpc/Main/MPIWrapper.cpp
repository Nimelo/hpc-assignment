/**
 * @file MPIWrapper.cpp
 * @brief Implementation of methods for MPIWrapper.
 */

#include "MPIWrapper.h"
#define MPI_DEFINE
#include <mpi.h>
double MPIWrapper::getTime()
{
		double value = 0.0;
		#ifdef MPI_DEFINE
			value = MPI_Wtime();
		#endif
		return value;
}

void MPIWrapper::init(int * argc, char *** argv)
{
	#ifdef MPI_DEFINE
		MPI_Init(argc, argv);
	#endif
}

long MPIWrapper::getCoreId()
{
	int coreId = 0;
	#ifdef MPI_DEFINE
		MPI_Comm_rank(MPI_COMM_WORLD, &coreId);
	#endif
	return (long)coreId;
}

long MPIWrapper::getQuantityOfCores()
{
	int coresQuantity = 0;
	#ifdef MPI_DEFINE
		MPI_Comm_size(MPI_COMM_WORLD, &coresQuantity);
	#endif
	return (long)coresQuantity;
}

void MPIWrapper::finalize()
{
	#ifdef MPI_DEFINE
		MPI_Finalize();
	#endif
}

void MPIWrapper::sendDoublesToCore(long coreId, int tag, double * doubles, long quantity)
{
	#ifdef MPI_DEFINE
		MPI_Send(doubles, quantity, MPI_DOUBLE, coreId, tag, MPI_COMM_WORLD);
	#endif
}

double MPIWrapper::receiveSingleDoubleFromCore(long coreId, int tag)
{
	double value = 0.0;
	#ifdef MPI_DEFINE
		MPI_Status status;
		MPI_Recv(&value, 1, MPI_DOUBLE, coreId, tag, MPI_COMM_WORLD, &status);
	#endif
	return value;
}

void MPIWrapper::receiveDoublesFromCore(long coreId, int tag, long quantity, double * storage)
{
	#ifdef MPI_DEFINE
		MPI_Status status;
		MPI_Recv(storage, quantity, MPI_DOUBLE, coreId, tag, MPI_COMM_WORLD, &status);

	#endif
}

void MPIWrapper::sendRecvDoubles(long sCoreId, long sQuantity, double * sBuff, int sTag, long rCoreId, long rQuantity, double * rBuff, int rTag)
{
	#ifdef MPI_DEFINE
		MPI_Status status;
		MPI_Sendrecv(sBuff, sQuantity, MPI_DOUBLE, sCoreId, sTag, rBuff, rQuantity, MPI_DOUBLE, rCoreId, rTag, MPI_COMM_WORLD, &status);
	#endif
}
