#include <pthread.h>
#include "../include/mutex.hpp"

mutex::mutex()
{
	pthread_mutex_init(&pthread_mutex, NULL);
}

mutex::~mutex()
{
	pthread_mutex_destroy(&pthread_mutex);
}

void mutex::lock()
{
	pthread_mutex_lock(&pthread_mutex);
}

void mutex::unlock()
{
	pthread_mutex_unlock(&pthread_mutex);

}

bool mutex::trylock()
{
	return (pthread_mutex_trylock(&pthread_mutex) == 0);
}

