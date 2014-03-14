# include <iostream>
#include <unistd.h>
#include <string.h>
#include "../include/producer.hpp"
#include "../include/data_entry.h"


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
		mtx->lock();
		if (queue->size() < num_entries)
		{
			// Add item to the queue
			entry.id    = &id;
			entry.count = ++counter;
			std::cout << "[" << id << "] adding work" << std::endl;
			queue->push(entry);

			// Signal to the other threads that they can execute
			c->broadcast();
		}
		mtx->unlock();

		if (counter >= num_entries)
		{
			running = false;
		}

		/*
		if (counter % 10 == 0)
		{
			sleep(2);
		}
		*/
	}
}
producer::~producer()
{
	std::cout << "[" << id << "] " << "producer destructor" << std::endl;
}

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
							      	
