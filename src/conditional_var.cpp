#include "../include/conditional_var.hpp"

conditional_var::conditional_var(mutex * mtx)
{
	this->mtx = mtx;
	pthread_cond_init(&pthread_cond, NULL);
}

conditional_var::~conditional_var() {}

void conditional_var::broadcast()
{
	pthread_cond_broadcast(&pthread_cond);
}

void conditional_var::wait()
{
	pthread_cond_wait(&pthread_cond, mtx->get_mutex());
}

