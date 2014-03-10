# include <iostream>
#include <unistd.h>
#include <sstream>
#include <string.h>
#include "../include/producer.hpp"
#include "../include/data_entry.h"

void producer::produce(size_t num_entries)
{
	std::cout << "[" << id << "] " << "produce..." << std::endl;
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
	std::cout << "[" << id << "] " << "producer.run" << std::endl;
	if (!queue)
	{
		return;
	}

	data_entry entry;
	unsigned long counter = 0;

	while (running)
	{
		for (size_t i = 0; i < num_entries; ++i)
		{
			entry.id    = &id;
			entry.count = ++counter;
			queue->push(entry);
			usleep(100);
		}
		sleep(2);
	}
}






							      	
