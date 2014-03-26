#define BOOST_TEST_MODULE blocking_queue test cases
#include <string>
#include <boost/test/unit_test.hpp>
#include "../include/blocking_queue.hpp"
#include "../include/mutex.hpp"
#include "../include/data_entry.h"

// ----------------------------------------------------------------------------
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

// ----------------------------------------------------------------------------
/**
 * Fixture to wrap a queue and handful of data_entry instances
 */
struct blocking_queue_wrapper
{
	blocking_queue<data_entry> * queue;
	mutex * mtx;

	data_entry entry1;
	data_entry entry2;
	data_entry entry3;
	data_entry entry4;
	std::string e1_id;
	std::string e2_id;
	std::string e3_id;
	std::string e4_id;
		
	blocking_queue_wrapper()
	{
		mtx = new mutex;
		queue = new blocking_queue<data_entry>(mtx);
		e1_id = "Entry 1";
		e2_id = "Entry 2";
		e3_id = "Entry 3";
		e4_id = "Entry 4";
	
		entry1.id = &e1_id;
		entry1.count = 1L;
		entry2.id = &e2_id;
		entry2.count = 2L;
		entry3.id = &e3_id;
		entry3.count = 3L;
		entry4.id = &e4_id;
		entry4.count = 4L;
	}                                                        	
	
	~blocking_queue_wrapper()
	{
		delete queue;
		delete mtx;
	}
};


/**
 * Tests the set_size and get_size accessor/mutator functions in the
 * blocking_queue implementation
 */
BOOST_FIXTURE_TEST_SUITE(set_size_tests, blocking_queue_wrapper)

BOOST_AUTO_TEST_CASE(non_zero_value)
{
	size_t size = 4;
	queue->set_size(size);
	BOOST_CHECK_EQUAL(queue->get_size(), size);
}

BOOST_AUTO_TEST_CASE(zero_value)
{
	size_t size = 0;
	size_t size_expected = 5;
	queue->set_size(size);
	BOOST_CHECK_EQUAL(queue->get_size(), size_expected);
}

BOOST_AUTO_TEST_SUITE_END()


// ----------------------------------------------------------------------------
/**
 * Tests the integrity of the internal data (queue) function.
 * That it will return items in FIFO order, and that items
 * that are added to the queue are the correct ones returned
 * in the order expected.
 */
BOOST_FIXTURE_TEST_SUITE(data_tests, blocking_queue_wrapper)

BOOST_AUTO_TEST_CASE(return_same_entry_that_is_added)
{
	queue->push(entry1);

	// Is one item on the queue?
	BOOST_CHECK_EQUAL(1U, queue->size());

	// Do we get back the item with the expected values?
	data_entry return_entry = queue->pop();
	BOOST_CHECK_EQUAL(0, e1_id.compare(*return_entry.id));
	BOOST_CHECK_EQUAL(1L, return_entry.count);
}

BOOST_AUTO_TEST_CASE(return_items_fifo)
{
	queue->push(entry1);
	queue->push(entry2);
	queue->push(entry3);

	BOOST_CHECK_EQUAL(3U, queue->size());

	// We should get back entry1 item/data
	data_entry return_entry1 = queue->pop();
	BOOST_CHECK_EQUAL(0, e1_id.compare(*return_entry1.id));
	BOOST_CHECK_EQUAL(1L, return_entry1.count);

	data_entry return_entry2 = queue->pop();

	data_entry return_entry3 = queue->pop();

	// Entry 3 should have the following values
	BOOST_CHECK_EQUAL(0, e3_id.compare(*return_entry3.id));
	BOOST_CHECK_EQUAL(3L, return_entry3.count);

	BOOST_CHECK_EQUAL(0, queue->size());
}

BOOST_AUTO_TEST_SUITE_END()

