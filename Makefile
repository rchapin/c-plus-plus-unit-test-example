CC		= g++ -DBOOST_TEST_DYN_LINK
DEBUG		= -g
CFLAGS		= -v -c -Wall $(DEBUG)
LFLAGS		= -v -Wall $(DEBUG)
LDFLAGS		= -lpcap -lconfig++
BOOST_LDFLAGS	= -L /usr/local/boost/stage/lib/ -lboost_unit_test_framework -lpthread

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
OBJS	= cpp-unit-test-example.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(LDFLAGS) $(BOOST_LDFLAGS) $^ -o $@

$(BUILD_DIR)/cpp-unit-test-example.o: cpp-unit-test-example.cpp
	$(CC) $(CFLAGS) $< -o $@

install:
	echo "Not yet implemented..." 

clean:
	\rm -rf ./bin/* ./build/*

test:
	echo "Not yet implemented..."
