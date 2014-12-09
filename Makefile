CC            = g++
BOOST_CC      = g++ -DBOOST_TEST_DYN_LINK
DEBUG         = -g
CFLAGS        = -v -c -Wall $(DEBUG)
LFLAGS        = -v -Wall $(DEBUG)
LDFLAGS       = -lpthread
# Compiled from source bost libs
# BOOST_LDFLAGS = -L /usr/local/boost/stage/lib/ -lboost_unit_test_framework -lpthread
BOOST_LDFLAGS = -L /usr/lib64/ -lboost_unit_test_framework

BIN_DIR       = bin
BUILD_DIR     = build
DIST_DIR      = dist
INC_DIR       = include
SRC_DIR       = src

vpath %.c   $(SRC_DIR)
vpath %.cpp $(SRC_DIR)
vpath %.h   $(INC_DIR)
vpath %.hpp $(INC_DIR)
vpath %.o   $(BUILD_DIR)

TARGET = $(BIN_DIR)/cpp-unit-test-example
OBJS   = cpp-unit-test-example.o thread.o mutex.o conditional_var.o producer.o consumer.o

BLOCKING_QUEUE_TEST_TARGET      = $(BIN_DIR)/blocking_queue_test
BLOCKING_QUEUE_TEST_TARGET_OBJS = blocking_queue_test.o mutex.o

all: $(TARGET) $(BLOCKING_QUEUE_TEST_TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/cpp-unit-test-example.o: cpp-unit-test-example.cpp producer.hpp \
 blocking_queue.hpp mutex.hpp mutex_t.hpp conditional_var.hpp data_entry.h \
 worker.hpp thread.hpp thread_t.hpp consumer.hpp blocking_queue.hpp \
 data_entry.h conditional_var.hpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/producer.o: producer.cpp producer.hpp blocking_queue.hpp \
 mutex.hpp mutex_t.hpp conditional_var.hpp data_entry.h worker.hpp thread.hpp \
 thread_t.hpp data_entry.h
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/consumer.o: consumer.cpp consumer.hpp blocking_queue.hpp \
 mutex.hpp mutex_t.hpp conditional_var.hpp data_entry.h thread.hpp \
 thread_t.hpp worker.hpp data_entry.h
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/thread.o: thread.cpp thread.hpp thread_t.hpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/mutex.o: mutex.cpp mutex.hpp mutex_t.hpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/conditional_var.o: conditional_var.cpp conditional_var.hpp \
 mutex.hpp mutex_t.hpp
	$(CC) $(CFLAGS) $< -o $@

install:
	@echo "Not yet implemented..." 

clean:
	$(info ******* cleaning ./bin/* and ./build/* *******)
	@rm -rf ./bin/* ./build/*

# Will run all of the tests
test:
	$(info ******* Running tests *******)
	@$(BIN_DIR)/blocking_queue_test --log_level=test_suite

$(BLOCKING_QUEUE_TEST_TARGET): $(BLOCKING_QUEUE_TEST_TARGET_OBJS)
	$(BOOST_CC) $(LFLAGS) $(LDFLAGS) $(BOOST_LDFLAGS) $^ -o $@

$(BUILD_DIR)/blocking_queue_test.o: $(INC_DIR)/blocking_queue_test.cpp blocking_queue.hpp
	$(BOOST_CC) $(CFLAGS) $< -o $@


