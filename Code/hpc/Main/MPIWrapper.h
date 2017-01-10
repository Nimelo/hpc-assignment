#ifndef __H_MPI_WRAPPER
#define __H_MPI_WRAPPER
#define MPI
#ifdef MPI
	#include <mpi.h>
#endif

class MPIWrapper
{
public:
	static void init(int * argc, char *** argv);
	static long getCoreId();
	static long getQuantityOfCores();
	static void finalize();
	static void sendDoublesToCore(long coreId, int tag, double * doubles, long quantity);
	static double receiveSingleDoubleFromCore(long coreId, int tag);
	static void receiveDoublesFromCore(long coreId, int tag, long quantity, double * storage);
};

#endif
