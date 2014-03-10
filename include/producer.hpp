#ifndef PRODUCER_HPP
#define	PRODUCER_HPP

#include <sstream>
#include <string>
#include "thread.hpp"
#include "blocking_queue.hpp"
#include "data_entry.h"

class producer : public thread
{
	private:
		std::ostringstream stream;
		blocking_queue<data_entry> * queue;
		std::string id;
		size_t num_entries;
		
	protected:
	       virtual void run();
	
	public:
		producer(blocking_queue<data_entry> * queue, std::string id)
			: queue(queue), id(id), num_entries(0) {}
		
		void produce(size_t num_entries);	
};

#endif

