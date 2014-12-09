#ifndef MUTEX_HPP_T
#define	MUTEX_HPP_T

#include <pthread.h>

/**
 * Interface for the mutex wrapper header. 
 */
class mutex_t
{
	public:
		virtual ~mutex_t() {}
		virtual void lock() = 0;
		virtual void unlock() = 0;
		virtual bool trylock() = 0;
		virtual pthread_mutex_t * get_mutex() = 0;
};
#endif
