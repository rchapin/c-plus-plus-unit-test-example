#include <csignal>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "../include/producer.hpp"
#include "../include/consumer.hpp"
#include "../include/blocking_queue.hpp"
#include "../include/data_entry.h"
#include "../include/conditional_var.hpp"

#define	DEFAULT_NUM_PRODUCERS 2
#define	DEFAULT_MAX_DATA_SIZE 15
#define	DEFAULT_NUM_CONSUMERS 3

// References defined in the global scope to enable access to them in the
// signal callback handler.
int num_producers, max_data_size, num_consumers;

mutex mtx;
conditional_var c(&mtx);
blocking_queue<data_entry> queue(&mtx);

producer * producers[DEFAULT_NUM_PRODUCERS];
consumer * consumers[DEFAULT_NUM_CONSUMERS];

/**
 * Callback handler registered to listen for the SIGINT signal and to then
 * shutdown all of the running threads.
 */	
void signal_callback_handler(int signum)
{
	std::cout << "Caught signal " << signum << std::endl;

	// Tell all of our threads to shutdown
	for (int i = 0; i < num_producers; ++i)
	{
		producers[i]->shutdown();
	}

	for (int i = 0; i < num_consumers; ++i)
	{
		consumers[i]->shutdown();
	}
}

int main(int argc, char* argv[])
{
	// Register the SIGINT signal and the signal handler
	std::signal(SIGINT, signal_callback_handler);

	std::cout << "Starting cpp-unit-test-example..." << std::endl;

	// Parse our command line arguments.
	int  arg_ints[3] {0, 0, 0};
	if ( argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
			arg_ints[(i - 1)] = atoi(argv[i]);
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		std::cout << "arg_ints[" << i << "] = " << arg_ints[i] << std::endl;
	}

	//
	// If we were passed a command line argument, override the default values
	// for the threads to instantiate.  Otherwise we use the constants.
	//
	if (arg_ints[0] != 0)
	{
		num_producers = arg_ints[0];
		producer * producers[num_producers];
	}
	else
	{
		num_producers = DEFAULT_NUM_PRODUCERS;
	}

	if (arg_ints[1] != 0)
	{
		max_data_size = arg_ints[1];
	}
	else
	{
		max_data_size = DEFAULT_MAX_DATA_SIZE;
	}

	if (arg_ints[2] != 0)
	{
		num_consumers = arg_ints[2];
		consumer * consumers[num_consumers];
	}
	else
	{
		num_consumers = DEFAULT_NUM_CONSUMERS;
	}

	//
	// Instantiate the producers and consumers
	//
	char buff [64];
	int n;

	for (int i = 0; i < num_producers; ++i)
	{
		// Concatenate the id for the producer
		n = sprintf(buff, "Producer %d", (i + 1));

		// Instantiate the producer and start the thread
		producers[i] = new producer(&queue, &mtx, &c, buff);
		producers[i]->produce(max_data_size);
	}
	
	for (int i = 0; i < num_consumers; ++i)
	{
		// Concatenate the id for the consumer
		n = sprintf(buff, "Consumer %d", (i + 1));

		// Instantiate the consumer and start the thread
		consumers[i] = new consumer(&queue, &mtx, &c, buff);
		consumers[i]->consume();
	}

	// Join the current thread on all of the new threads
	for (int i = 0; i < num_producers; ++i)
	{
		producers[i]->join();
	}

	for (int i = 0; i < num_consumers; ++i)
	{
		consumers[i]->join();
	}


	// Delete our instances and set the pointers to NULL
	for (int i = 0; i < num_producers; ++i)
	{
		delete producers[i];
		producers[i] = NULL;
	}

	for (int i = 0; i < num_consumers; ++i)
	{
		delete consumers[i];
		consumers[i] = NULL;
	}

	return (0);
}
