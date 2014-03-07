// #include <string>
# include <iostream>
#include <unistd.h>
#include "../include/producer.hpp"

void producer::produce(size_t num_entries)
{
	std::cout << "produce..." << std::endl;
	if (!queue)
	{
		return;
	}
	if (num_entries <= 0 )
	{
		return;
	}

	this->num_entries = num_entries;
	start();
}


void producer::run()
{
	std::cout << "producer.run" << std::endl;
	if (!queue)
	{
		return;
	}
	for (size_t i = 0; i < num_entries; ++i)
	{
		queue->push(id);
		usleep(100);
	}
}


