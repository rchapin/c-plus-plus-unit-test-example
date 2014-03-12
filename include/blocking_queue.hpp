#ifndef BLOCKING_QUEUE_HPP
#define	BLOCKING_QUEUE_HPP

#include <queue>
# include <iostream>
#include "mutex.hpp"

/**
 * A blocking queue implementation for the producer/consumer example
 *
 * @author	Ryan Chapin
 */
template <class T> class blocking_queue
{
	private:
		std::queue<T> data;
		mutex * mtx;
		size_t max_data_size;
		size_t spin_time;

	public:
		blocking_queue(mutex * mtx) : mtx(mtx) {}
		
		~blocking_queue()
		{
			std::cout << "blocking_queue destructor" << std::endl;
			mtx->lock();
			while (data.size())
			{
				data.pop();
			}
			mtx->unlock();
		}

		void set_size(size_t max_data_size)
		{
			this->max_data_size = max_data_size;
		}
		
		size_t size() const
		{
			size_t retval = data.size();
			return (retval);
		}
		
		void push(T entry)
		{
			data.push(entry);
		}

		T pop()
		{
			T retval = data.front();
			data.pop(); 
			return (retval);
		}
};

#endif
