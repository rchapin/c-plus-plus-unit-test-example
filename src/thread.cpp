#include <iostream>

#include "../include/thread.hpp"

thread::thread() {}

thread::~thread() {}

void * thread::execute(void * ptr)
{
	std::cout << "execute" << std::endl;
	if (!ptr) {
		return (0);
	}

	// Since we know that the type of the ptr will be a thread instance
	// we can do the least expensive cast to get a pointer to a thread.
	// Then we can invoke the run function.
	static_cast<thread *>(ptr)->run();

	pthread_exit(ptr);
	return (0);
}

void thread::start()
{
	std::cout << "start" << std::endl;

	// Create a new thread, returning it to the pthread member in the
	// class, and passing 'this' as the pointer to later be cast as a
	// thread instance and then have the run method invoked.
	pthread_create(&pthread, NULL, thread::execute, this);
}

void thread::join()
{
	pthread_join(pthread, NULL);
}


