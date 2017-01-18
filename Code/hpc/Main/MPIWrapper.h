/**
 * @file MPIWrapper.h
 * @brief Declaration of methods for MPIWrapper.
 */

#ifndef __H_MPI_WRAPPER
#define __H_MPI_WRAPPER

/**
 * @brief Implementaion wrapper for MPI connections.
 * @see MPI
 * @author Mateusz Gasior
 */
class MPIWrapper
{
public:
	/**
	 * Initializes MPI.
	 * @param argc Pointer to count of arguments.
	 * @param argv Pointer to two dimensial array of command line parameters.
	 */
	static void init(int * argc, char *** argv);

	/**
	 * Returns current time of MPI applciation.	
	 * @value Current time.
	 */
	static double getTime();

	/**
	 * Returns current core id.
	 * @value Current core id.
	 */
	static long getCoreId();
	
	/**
	 * Returns quantity of reserved cores.
	 * @value Quantity of reserved cores.
	 */
	static long getQuantityOfCores();

	/**
	 * Finalizes MPI.
         */
	static void finalize();
	
	/**
	 * Sends doubles to core.
	 * @param coreId Desitination core id.
	 * @param tag Tag for message.
	 * @param doubles Array of doubles.
	 * @param quantity Quantity of elements in array.
	 */
	static void sendDoublesToCore(long coreId, int tag, double * doubles, long quantity);

	/**
	 * Returns double from different core.
 	 * @param coreId Id of core to receive message.
	 * @param tag Tag of message.
	 * @return Double value received from different core.
	 */
	static double receiveSingleDoubleFromCore(long coreId, int tag);

	/**
	 * Returns doubles from different core and stores them in given array.
 	 * @param coreId Id of core to receive message.
	 * @param tag Tag of message.
	 * @param quantity Expected amount of values.
	 * @param storage Pointer to the first element for received data.
	 */
	static void receiveDoublesFromCore(long coreId, int tag, long quantity, double * storage);

	/**
	 * Sends and receives doubles for different cores.
 	 * @param sCoreId Id of core to send message.
	 * @param sQuantity Quantity of doubles to be send.
	 * @param sBuff Buffer of doubles to be send.
	 * @param sTag Tag for sending message.
	 * @param rCoreId Id of core to receive message.
	 * @param rQuantity Quantity of doubles to be received.
	 * @param rBuff Buffer of doubles for storage received values.
	 * @param rTag Tag for sending received.
	 */
	static void sendRecvDoubles(long sCoreId, long sQuantity, double * sBuff, int sTag, long rCoreId, long rQuantity, double * rBuff, int rTag);
};

#endif
