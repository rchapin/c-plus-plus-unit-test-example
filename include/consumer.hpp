#ifndef CONSUMER
#define	CONSUMER

#include <string>
#include "blocking_queue.hpp"
#include "data_entry.h"
#include "thread.hpp"
#include "mutex.hpp"

class consumer : public thread
{
	private:
		blocking_queue<data_entry> * queue;
		mutex * mtx;
		std::string id;
		
	protected:
		virtual void run();

	public:
		consumer(blocking_queue<data_entry> * queue, mutex * mtx, std::string id)
			: queue(queue), mtx(mtx), id(id) {}

		~consumer();

		void consume();
};

#endif

