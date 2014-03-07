#ifndef MUTEX_HPP
#define	MUTEX_HPP

#include <pthread.h>

/**
 * Wrapping class for the pthread_mutex_t C API.
 */
class mutex
{
	private:
		pthread_mutex_t pthread_mutex;

	public:
		mutex();
		~mutex();

		void lock();
		void unlock();
		bool trylock();
};

#endif
