#ifndef PRODUCER_CONSUMER_T
#define PRODUCER_CONSUMER_T

/**
 * Producer/consumer interface example.  This interface for this class
 * encapsulates the instantiation and management of the various threads
 * needed to demonstrate the system.
 */
template <class mutex*>
class producer_consumer_t
{
	virtual ~producer_consumer_t() {};

	/**
	 * Sets the number of producer threads for the system.
	 *
	 * @param[in]	Number of producer threads desired.
	 */	
	virtual void set_producer_size(size_t producer_num) = 0;

	/**
	 * Get the number of producer threads configured.
	 *
	 * @return	Number of producer threads configured.
	 */
	virtual const &size_t get_producer_size() = 0;

	virtual void set_queue_size(size_t queue_size) = 0;

	virtual const &size_t get_queue_size() = 0;
	
	/**
	 * Sets the number of consumer threads for the system.
	 *
	 * @param[in]	Number of consumer threads desired.
	 */
	virtual void set_consumer_size(size_t consumer_num) = 0;
	
	/**
	 * Returns the current number of consumer threads configured.
	 *
	 * @return	Number of consumer threads configured. 
	 */
	virtual const &size_t get_consumer_size() = 0;
	
	/**
	 * Starts the system running
	 */
	virtual void start() = 0;
	
	/**
	 * Cleanly shuts down the system
	 */
	virtual void shutdown() = 0;
};

#endif
