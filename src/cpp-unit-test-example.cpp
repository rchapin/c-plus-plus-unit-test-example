#include <iostream>
#include <string>
//#include "../include/thread.hpp"
#include "../include/producer.hpp"
#include "../include/blocking_queue.hpp"

class thread_conc : public thread
{
	protected:
		virtual void run();
};

void thread_conc::run()
{
 	std::cout << "From thread_conc run" << std::endl;
}

int main()
{
	std::cout << "Hello World!" << std::endl;

/*
	thread_conc t1;
	t1.start();
	t1.join();
*/

	size_t max_data_size = 10;
 	blocking_queue<std::string> queue;
  	producer prod(&queue, "Producer 1");
	prod.produce(10);
	prod.join();
	return (0);
}
