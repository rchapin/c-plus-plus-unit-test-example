CC		= g++
BOOST_CC	= g++ -DBOOST_TEST_DYN_LINK
DEBUG		= -g
CFLAGS		= -v -c -Wall $(DEBUG)
LFLAGS		= -v -Wall $(DEBUG)
LDFLAGS		= -lpthread
BOOST_LDFLAGS	= -L /usr/local/boost/stage/lib/ -lboost_unit_test_framework 

BIN_DIR		= bin
BUILD_DIR	= build
DIST_DIR	= dist
INC_DIR		= include
SRC_DIR		= src
TEST_DIR	= test

vpath %.c $(SRC_DIR)
vpath %.cpp $(SRC_DIR)
vpath %.h $(INC_DIR)
vpath %.hpp $(INC_DIR)
vpath %.o $(BUILD_DIR)

TARGET	= $(BIN_DIR)/cpp-unit-test-example
OBJS	= cpp-unit-test-example.o thread.o mutex.o conditional_var.o producer.o consumer.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/cpp-unit-test-example.o: cpp-unit-test-example.cpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/producer.o: producer.cpp producer.hpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/consumer.o: consumer.cpp consumer.hpp worker.hpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/thread.o: thread.cpp thread.hpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/mutex.o: mutex.cpp mutex.hpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/conditional_var.o: conditional_var.cpp conditional_var.hpp
	$(CC) $(CFLAGS) $< -o $@

install:
	echo "Not yet implemented..." 

clean:
	\rm -rf ./bin/* ./build/*

test:
	echo "Not yet implemented..."
