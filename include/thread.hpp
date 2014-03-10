#ifndef THREAD
#define	THREAD

#include <pthread.h>

/**
 * Abstract base class for threads.
 */
class thread
{
	private:
		pthread_t pthread;
		
		/**
		 * Member function to be pointed to as the function to be
		 * threaded.  This is a framework function that is used to
		 * then invoke the run() function in the concrete sub-class of
		 * thread.
		 */
		static void * execute(void *);

	protected:

		/**
		 * Pure virtual function to be implemented in the concrete sub-
		 * classes of thread.
		 */
		virtual void run() = 0;

		/**
		 * Flag to enable us to shutdown a thread instance
		 */
		bool running;

	public:
		thread() : running(false) {}
		virtual ~thread();

		/**
		 * Instantiates a new thread.
		 */
		void start();

		/**
		 * Interface to allow other threads to join on the running
		 * pthread instance.
		 */
		void join();

		void shutdown();
};

#endif

