#define BOOST_TEST_MODULE blocking_queue test cases
#include <boost/test/unit_test.hpp>
#include "../include/blocking_queue.hpp"
#include "../include/mutex.hpp"
#include "../include/data_entry.h"

BOOST_AUTO_TEST_SUITE(constructor_tests)

/**
 * Fixture to enable the instantiation of a clean mutex instance to be used
 * for tests that require it.
 */
struct mutex_fixture
{
	mutex * mtx;
	mutex_fixture()  { mtx = new mutex; }
	~mutex_fixture() { delete mtx; }
};

/**
 * Tests that the blocking_queue.mtx member will be set properly when passing
 * a pointer to a mutex instance to the constructor.
 */
BOOST_FIXTURE_TEST_CASE(with_mtx_arg, mutex_fixture)
{
	blocking_queue<data_entry> * bq = new blocking_queue<data_entry>(mtx);
	BOOST_CHECK(bq->get_mtx() != NULL);
	delete bq;
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(set_size_tests)

struct blocking_queue_wrapper
{
	blocking_queue<data_entry> * queue;
	mutex * mtx;
	blocking_queue_wrapper()
	{
		mtx = new mutex;
		queue = new blocking_queue<data_entry>(mtx); 
	}                                                        	
	
	~blocking_queue_wrapper()
	{
		delete queue;
		delete mtx;
	}
};

BOOST_FIXTURE_TEST_CASE(non_zero_value, blocking_queue_wrapper)
{
	size_t size = 4;
	queue->set_size(size);
	BOOST_CHECK_EQUAL( queue->get_size(), size);
}

BOOST_AUTO_TEST_SUITE_END()



								 
