#ifndef WORKER_HPP
#define	WORKER_HPP

#include "thread.hpp"

class worker : public thread
{
	protected:
		blocking_queue<data_entry> * queue;
		mutex * mtx;
		conditional_var * c;
		std::string id;

	public:
		worker(blocking_queue<data_entry> * queue, mutex * mtx, conditional_var * c, std::string id)
			: queue(queue), mtx(mtx), c(c), id(id) {}

};

#endif

