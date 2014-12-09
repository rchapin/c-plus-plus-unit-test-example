#ifndef MUTEX_HPP
#define	MUTEX_HPP

#include <pthread.h>
#include "mutex_t.hpp"

/**
 * Wrapping class for the pthread_mutex_t C API.
 *
 * @author	Ryan Chapin
 */
class mutex : public mutex_t
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
