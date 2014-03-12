#ifndef CONDITIONAL_VAR_HPP
#define	CONDITIONAL_VAR_HPP

#include <pthread.h>
#include "mutex.hpp"

/**
 * Wrapper class for the pthread_cond_t C API.
 */
class conditional_var
{
	private:
		pthread_cond_t pthread_cond;
		mutex * mtx;

	public:
		conditional_var(mutex * mtx);
		~conditional_var();

		void broadcast();
		void wait();
};

#endif
					 
