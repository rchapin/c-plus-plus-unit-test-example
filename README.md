# c-plus-plus-unit-test-example

A working example of a c++ project with unit tests and mock objects.  The example program is a multi-threaded, producer/consumer excersize.

# Compiling

The following are dependencies to compile this program:

- libpcap-devel-1.0.0
- libpcap-1.0.0
- boost_1_54_0

Both libpcap and libpcap-devel were installed via yum.

Boost was compiled from source:

- Unpack the archive into /usr/local and create the following symlink:

```
# ln -s ./boost_1_54_0 ./boost
```
- From within the /usr/local/boost dir invoke the following commands to compile boost

```
# ./boostrap.sh
# ./b2
```

- The libs end up in /usr/local/boost_1_54_0/staged/libs

Once the dependencies are installed simply compile via:

```
make
```

# Running

Once compiled it can be run with the default values for the producer count, the queue size, and consumer count by invoking

```
./bin/cpp-unit-test-example
```

It optionally accepts three int arguments:

```
cpp-unit-test-example [optional [num-producers] [queue-size] [num-consumers]]
```

If it is passed only two int arguments, that will set the num-producers and queue-size.  If it is passed ```2 0 9``` it will set num-producers to 2, use the default value for queue-size, and set the num-consumers to 9.

Ctrl-C will gracefully shutdown the program as it listens for and shutsdown on SIGINT signals.

