#ifndef CONSUMER_HPP
#define	CONSUMER_HPP

#include <string>
#include "blocking_queue.hpp"
#include "conditional_var.hpp"
#include "data_entry.h"
#include "mutex.hpp"
#include "thread.hpp"
#include "worker.hpp"

/**
 * Genric consumer class for producer/consumer example.
 *
 * @author	Ryan Chapin
 */
class consumer : public worker
{
	protected:
		virtual void run();

	public:
		consumer(blocking_queue<data_entry> * queue, mutex * mtx, conditional_var * c, std::string id)
			: worker(queue, mtx, c, id) {}

		~consumer();

		void consume();

		virtual void shutdown();
};

#endif

