#include <queue>
#include <unistd.h>
#include "../include/blocking_queue.hpp"

template <class T> blocking_queue<T>::blocking_queue()
{
	// This will get removed once the pthread_cond_t is implemented
	this->spin_time = 50;
}
		   
template <class T> blocking_queue<T>::~blocking_queue()
{
	mtx.lock();
	while (data.size())
	{
		data.pop();
	}
	mtx.unlock();
}

template <class T> void blocking_queue<T>::set_size(size_t max_data_size)
{
	this->max_data_size = max_data_size;
}

template <class T> size_t blocking_queue<T>::size() const
{
	mtx.lock();
	size_t retval = data.size();
	mtx.unlock();
	return (retval);
}

template <class T> void blocking_queue<T>::push(T entry)
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

template <class T> T blocking_queue<T>::pop()
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
				 
