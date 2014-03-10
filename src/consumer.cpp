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
		std::cout << "[" << id << "] " << "consumer.running before" << std::endl;
		mtx->lock();
	
		// std::string entry = queue->pop();
		data_entry entry = queue->pop();
	
		mtx->unlock();
		std::cout << "[" << id << "] " << " => [" << id << "] : " << * entry.id << ", " << entry.count << std::endl;
		std::cout << "[" << id << "] " << "consumer.running after" << std::endl;
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




