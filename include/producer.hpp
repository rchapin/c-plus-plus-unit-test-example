#ifndef PRODUCER_HPP
#define	PRODUCER_HPP

#include <string>
#include "thread.hpp"
#include "blocking_queue.hpp"

class producer : public thread
{
	private:
		blocking_queue<std::string> * queue;
		std::string id;
		size_t num_entries;
		
	protected:
	       virtual void run();
	
	public:
		producer(blocking_queue<std::string> * queue, std::string id)
			: queue(queue), id(id), num_entries(0) {}
		
		void produce(size_t num_entries);	

};

#endif

