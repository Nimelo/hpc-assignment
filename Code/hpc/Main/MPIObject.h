#ifndef __H_MPI_OBJECT_H
#define __H_MPI_OBJECT_H

class MPIObject
{
protected:
	long coreId;
	long coresQuantity;
public:
	MPIObject(long coreId, long coresQuantity)
		: coreId(coreId), coresQuantity(coresQuantity)
	{
	}
};

#endif
