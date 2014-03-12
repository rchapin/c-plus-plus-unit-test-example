#include <iostream>
#include <string>
#include "../include/consumer.hpp"
#include "../include/data_entry.h"

void consumer::run()
{
	std::cout << "[" << id << "] " << "consumer.run" << std::endl;
	
	if (!this->queue || !this->mtx)
	{
		return;
	}

	while (running)
	{
		data_entry entry;

		mtx->lock();
		std::cout << "[" << id << "] " << "consumer.running before" << std::endl;
	
		if (queue->size() == 0)
		{
			// There is no work to do right now
			c->wait();
		} else
		{
			// Get work from the queue
			std::cout << "[" << id << "] getting work from the queue" << std::endl;
			entry = queue->pop();
			std::cout << "[" << id << "] : " << * entry.id << ", " << entry.count << std::endl;
		}
		
		std::cout << "[" << id << "] " << "consumer.running after" << std::endl;
		mtx->unlock();
	}


}

consumer::~consumer()
{
	std::cout << "[" << id << "] " << "consumer destructor" << std::endl;

}

void consumer::consume()
{
	std::cout << "[" << id << "] " << "consumer.consume" << std::endl;
	
	if (!queue || !mtx)
	{
		return;
	}

	start();
}

void consumer::shutdown()
{
	running = false;
	c->broadcast();
}



