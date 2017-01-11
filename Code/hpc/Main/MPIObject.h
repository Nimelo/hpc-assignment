/**
 * @file MPIObject.h
 * @brief Declaration of methods for MPIObject.
 */

#ifndef __H_MPI_OBJECT_H
#define __H_MPI_OBJECT_H


/**
 * @brief Implementaion of MPIObject. 
 * Each of the MPIObject should have indicator of current core and total amount of reserved cores.
 * @author Mateusz Gasior
 */
class MPIObject
{
protected:
	/**
	 * Current core id.
	 */
	long coreId;

	/**
	 * Quantity of reserved cores.
	 */
	long coresQuantity;
public:
	/**
	 * Default constructor.
	 * @param coreId Current core id.
	 * @param coresQuantity Quantity of reserved cores.
	 */
	MPIObject(long coreId, long coresQuantity)
		: coreId(coreId), coresQuantity(coresQuantity)
	{
	}
};

#endif
