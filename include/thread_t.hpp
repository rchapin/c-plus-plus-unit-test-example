#ifndef THREAD_I
#define	THREAD_I

/**
 * Interface for thread classes.
 *
 * @author	Ryan Chapin
 */
class thread_t
{
	public:
		virtual ~thread_t() {};

		/**
		 * Instantiates a new thread.
		 */
		virtual void start() = 0;

		/**
		 * Interface to allow other threads to join on the running
		 * pthread instance.
		 */
		virtual void join() = 0;

		/**
		 * Tells the thread to finish the work that it is doing and to
		 * exit cleanly.
		 */
		virtual void shutdown() = 0;
};

#endif

