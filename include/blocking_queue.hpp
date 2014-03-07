#ifndef BLOCKING_QUEUE_HPP
#define	BLOCKING_QUEUE_HPP

# include <queue>
#include <unistd.h>
#include "mutex.hpp"

template <class T> class blocking_queue
{
	private:
		std::queue<T> data;
		mutex mtx;
		size_t max_data_size;
		size_t spin_time;

	public:
		blocking_queue() {}
		
		~blocking_queue()
		{
			mtx.lock();
			while (data.size())
			{
				data.pop();
			}
			mtx.unlock();
		}

		void set_size(size_t max_data_size)
		{
			this->max_data_size = max_data_size;
		}
		
		size_t size() const
		{
			mtx.lock();
			size_t retval = data.size();
			mtx.unlock();
			return (retval);
		}
		
		void push(T entry)
		{
			mtx.lock();

			while (data.size() >= this->max_data_size)
			{
				mtx.unlock();
				usleep(spin_time);
				mtx.lock();
			}

			data.push(entry);
			mtx.unlock();
		}

		T pop()
		{
		 	mtx.lock();

			while (data.size() <= 0)
			{
				mtx.unlock();
				usleep(spin_time);
				mtx.lock();
			}
	
			T retval = data.front();
			data.pop(); 
			mtx.unlock();
			return (retval);

		}
};

#endif
