#ifndef CONSUMER_HPP
#define	CONSUMER_HPP

#include <string>
#include "blocking_queue.hpp"
#include "data_entry.h"
#include "thread.hpp"
#include "mutex.hpp"
#include "conditional_var.hpp"

/**
 * Genric consumer class for producer/consumer example.
 *
 * @author	Ryan Chapin
 */
class consumer : public thread
{
	private:
		blocking_queue<data_entry> * queue;
		mutex * mtx;
		conditional_var * c;
		std::string id;
		
	protected:
		virtual void run();

	public:
		consumer(blocking_queue<data_entry> * queue, mutex * mtx, conditional_var * c, std::string id)
			: queue(queue), mtx(mtx), c(c), id(id) {}

		~consumer();

		void consume();

		virtual void shutdown();
};

#endif

