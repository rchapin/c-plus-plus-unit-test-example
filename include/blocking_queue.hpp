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

		/**
		 * Default size set for the max_data_size
		 * if a 0 or - value is set.
		 */ 
		const static int max_data_size_default = 5;

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

		/**
		 * Return a pointer to the mtx member
		 *
		 * @return mutex pointer.
		 */
		mutex * get_mtx()
		{
			return (this->mtx);
		}

		/**
		 * Set the maximum number of items that will be allowed to be
		 * stored on the queue.  After exceeding the max_data_size
		 * number of items, invocations to @see push(T entry) by
		 * producers will block.
		 *
		 * @param[in] max_data_size The setting for max_data_size.
		 */ 
		void set_size(size_t max_data_size)
		{
			if ( max_data_size <= 0 )
			{
				this->max_data_size = blocking_queue::max_data_size_default;
			} else
			{
				this->max_data_size = max_data_size;
			}
		}

		/**
		 * Will return the current setting for the max_data_size member
		 *
		 * @return size_t of the max_data_size member.
		 */
		size_t get_size()
		{
			return (this->max_data_size);
		}
		
		/**
		 * Get the current number of items on the queue.
		 *
		 * @return Number of items on the queue.
		 */
		size_t size() const
		{
			size_t retval = data.size();
			return (retval);
		}
		
		/**
		 * Add an item onto the queue
		 *
		 * @param[in]	entry An entry of type <T> to be added to the
		 *                    queue.
		 */
		void push(T entry)
		{
			data.push(entry);
		}

		/**
		 * Grab the oldest (FIFO) item from the queue.
		 *
		 * @return entry of type <T>.
		 */
		T pop()
		{
			T retval = data.front();
			data.pop(); 
			return (retval);
		}
};

#endif
