#include <iostream>
#include <string>
//#include "../include/thread.hpp"
#include "../include/producer.hpp"
#include "../include/consumer.hpp"
#include "../include/blocking_queue.hpp"
#include "../include/data_entry.h"

/*
class thread_conc : public thread
{
	protected:
		virtual void run();
};

void thread_conc::run()
{
 	std::cout << "From thread_conc run" << std::endl;
}
*/

int main()
{
	std::cout << "Hello World!" << std::endl;

/*
	thread_conc t1;
	t1.start();
	t1.join();
*/

	size_t max_data_size = 10;
 	blocking_queue<data_entry> queue;
  	mutex mtx;

	producer prod(&queue, "Producer 1");
	prod.produce(10);

	consumer cons1(&queue, &mtx, "Consumer 1");
	cons1.consume();
	consumer cons2(&queue, &mtx, "Consumer 2");
	cons2.consume();

	prod.join();
	cons1.join();

	return (0);
}
