#ifndef PRODUCER_HPP
#define	PRODUCER_HPP

#include <string>
#include "blocking_queue.hpp"
#include "conditional_var.hpp"
#include "data_entry.h"
#include "mutex.hpp"
#include "worker.hpp"

/**
 * Generic producer class that will create data entries and place them on
 * a queue to be consumed by a consumer.
 *
 * @author	Ryan Chapin
 */
class producer : public worker
{
	private:
		size_t num_entries;
		
	protected:
	       virtual void run();
	
	public:
		producer(blocking_queue<data_entry> * queue, mutex * mtx,
			conditional_var * c, std::string id, size_t num_entries)
			: worker(queue, mtx, c, id)
		{
			this->num_entries = num_entries;
		}
		
		~producer();

		/**
		 * The public method that will start the thread running.
		 *
		 * @param[in]	num_entries The maximum number of items that
		 *		            will be stored on the queue.
		 */
		// void produce(size_t num_entries);	
};

#endif

