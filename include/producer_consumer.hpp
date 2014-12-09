#ifndef	PRODUCER_CONSUMER
#define	PRODUCER_CONSUMER

#include "producer_consumer_t.hpp"
#include "producer.hpp"
#include "consumer.hpp"
#include "blocking_queue.hpp"
#include "data_entry.h"
#include "conditional_var.hpp"

#define	DEFAULT_NUM_PRODUCERS 2
#define	DEFAULT_MAX_DATA_SIZE 15
#define	DEFAULT_NUM_CONSUMERS 3

template <class mutex*>
class producer_consumer : public producer_consumer_t<mutex*>
{

	private:
		size_t producer_num;
		size_t queue_size;
		size_t consumer_num;
		mutex * mtx;
		conditional_var cond_var;
		blocking_queue<data_entry> queue;

	public:

		producer_consumer(mutex * mtx) : mtx(mtx) {};

		producer_consumer(mutex* mtx, size_t producer_num, size_t queue_size, size_t consumer_num)
			: mtx(mtx), producer_num(producer_num), queue_size(queue_size), consumer_num(consumer_num) {}

		~producer_consumer() {}

		void set_producer_size(size_t producer_num);
		
		const &size_t get_producer_size();

		void set_queue_size(size_t queue_size);

		const &size_t get_queue_size();
	
		void set_consumer_size(size_t consumer_num);
	
		const &size_t get_consumer_size();

		void start();
	
		void shutdown();
};

#endif

