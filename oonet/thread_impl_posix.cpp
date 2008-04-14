/**
@file thread_impl_posix.cpp
@brief Implementation of thread class on Posix Platform
*/
#include "./thread.hpp"

namespace oonet
{
	namespace mt
	{
        void thread::_system_start(void)
        {
            // Check if an instance already exists
            if (b_running == true)
            {
                OONET_THROW_EXCEPTION(ExceptionThreadAlreadyStarted,
					"Thread alreay running!"
				);
                return;   // Error thread already started
            }

            // Check if previous wasn't joined, else join with it
            if (!b_joined)
                join(Infinity);

            // Start Thread
            int ret_error = pthread_create(&thread_h, NULL, this->_thread_func, this);
            if (ret_error != 0)
            {
                thread_h = 0; 		// We must reset it to default because specification says
                                    // that if pthread_create fails the value is undefined

                switch(ret_error)
                {
                case EAGAIN:
                    OONET_THROW_EXCEPTION(ExceptionTryAgain,
                        "Cannot start thread, you must try later, or maximum threads reached!");
                    break;
                default:
                    OONET_THROW_EXCEPTION(ExceptionSystemError,
                        "Cannot start thread for unknown reason..");
                    break;
				};
                return;	// Error on starting the thread
            }

            // Thread started...
            b_joined = false;
            b_running = true;
            return;		// Thread started succesfully
        }

        void thread::_system_join(ulong tm_timeoutms)
        {   OONET_DEBUG_L2("Thread::_linux_join()_\n");

            // Skip if thread is already joine
            if (b_joined)
                return;

            // For join
			if (tm_timeoutms == Infinity)
            {
                if (pthread_join(thread_h, NULL) != 0)
                {
                    switch(errno)
                    {
                    case EINVAL:
						OONET_THROW_EXCEPTION(ExceptionNotSupported,
							"This implementation of pthread doens't create joinable theads");
                        return;
                    default:
						OONET_THROW_EXCEPTION(ExceptionSystemError,
							"Unknown error when trying to join thread");
                        return;
                    }
                }
                // Ok thread joined
                b_joined = true;
                return;
            }
            else
                // No linux implementation for time out
                return _soft_join(tm_timeoutms);
        }

        // Stops the calling thread for a period of time
        void thread::sleep(ulong tm_sleepms)
        {	int err;
			err = usleep( tm_sleepms * 1000);		// Unix usleep gets microseconds
			if (err == EINTR)
				OONET_THROW_EXCEPTION(ExceptionInterrupted,
					"Thread::Sleep() Action interrupted by a singal!");
        }

	};	// !mt namespace
};	// !oonet namespace
