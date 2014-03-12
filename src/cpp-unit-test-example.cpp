#include <csignal>
#include <iostream>
#include <stdio.h>
#include <string>
#include "../include/producer.hpp"
#include "../include/consumer.hpp"
#include "../include/blocking_queue.hpp"
#include "../include/data_entry.h"
#include "../include/conditional_var.hpp"

#define	NUM_PRODUCERS 3
#define	MAX_DATA_SIZE 10
#define	NUM_CONSUMERS 5

mutex mtx;
conditional_var c(&mtx);
blocking_queue<data_entry> queue(&mtx);

producer * producers[NUM_PRODUCERS];
consumer * consumers[NUM_CONSUMERS];
					
	
void signal_callback_handler(int signum)
{
	std::cout << "Caught signal " << signum << std::endl;

	// Tell all of our threads to shutdown
	for (int i = 0; i < NUM_PRODUCERS; ++i)
	{
		producers[i]->shutdown();
	}

	for (int i = 0; i < NUM_CONSUMERS; ++i)
	{
		consumers[i]->shutdown();
	}
}

int main()
{
	// Register the SIGINT signal and the signal handler
	std::signal(SIGINT, signal_callback_handler);

	std::cout << "Starting cpp-unit-test-example..." << std::endl;

	char buff [64];
	int n;

	for (int i = 0; i < NUM_PRODUCERS; ++i)
	{
		// Concatenate the id for the producer
		n = sprintf(buff, "Producer %d", (i + 1));

		// Instantiate the producer and start the thread
		producers[i] = new producer(&queue, &mtx, &c, buff);
		producers[i]->produce(MAX_DATA_SIZE);
	}
	
	for (int i = 0; i < NUM_CONSUMERS; ++i)
	{
		// Concatenate the id for the consumer
		n = sprintf(buff, "Consumer %d", (i + 1));

		// Instantiate the consumer and start the thread
		consumers[i] = new consumer(&queue, &mtx, &c, buff);
		consumers[i]->consume();
	}

	// Join the current thread on all of the new threads
	for (int i = 0; i < NUM_PRODUCERS; ++i)
	{
		producers[i]->join();
	}

	for (int i = 0; i < NUM_CONSUMERS; ++i)
	{
		consumers[i]->join();
	}


	// Delete our instances and set the pointers to NULL
	for (int i = 0; i < NUM_PRODUCERS; ++i)
	{
		delete producers[i];
		producers[i] = NULL;
	}

	for (int i = 0; i < NUM_CONSUMERS; ++i)
	{
		delete consumers[i];
		consumers[i] = NULL;
	}

	return (0);
}
