#ifndef MUTEX_HPP
#define	MUTEX_HPP

#include <pthread.h>

/**
 * Wrapping class for the pthread_mutex_t C API.
 *
 * @author	Ryan Chapin
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
		pthread_mutex_t * get_mutex();
};

#endif
