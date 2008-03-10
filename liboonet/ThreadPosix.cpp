/**
@file ThreadPosix.cpp
@brief Implementation of Thread class on Posix Platform
*/
#include "Thread.h"

namespace OONet
{
	namespace MT
	{

        void Thread::_system_start(void) throw(Exception)
        {
            // Check if an instance already exists
            if (bRunning == true)
            {
                OONET_THROW_EXCEPTION(ExceptionThreadAlreadyStarted,
					_T("Thread alreay running!")
				);
                return;   // Error thread already started
            }

            // Check if previous wasn't joined, else join with it
            if (!bJoined)
                join(Infinity);

            // Start Thread
            int ret_error = pthread_create(&hThread, NULL, this->_thread_func, this);
            if (ret_error != 0)
            {
                hThread = 0; 		// We must reset it to default because specification says
                                    // that if pthread_create fails the value is undefined

                switch(ret_error)
                {
                case EAGAIN:
                    OONET_THROW_EXCEPTION(ExceptionTryAgain,
                        _T("Cannot start thread, you must try later, or maximum threads reached!"));
                    break;
                default:
                    OONET_THROW_EXCEPTION(ExceptionSystemError,
                        _T("Cannot start thread for unknown reason.."));
                    break;
				};
                return;	// Error on starting the thread
            }

            // Thread started...
            bJoined = false;
            bRunning = true;
            return;		// Thread started succesfully
        }

        void Thread::_system_join(ulong tm_timeoutms) throw(Exception)
        {   OONET_DEBUG_L2("Thread::_linux_join()_\n");

            // Skip if thread is already joine
            if (bJoined)
                return;

            // For join
			if (tm_timeoutms == Infinity)
            {
                if (pthread_join(hThread, NULL) != 0)
                {
                    switch(errno)
                    {
                    case EINVAL:
						OONET_THROW_EXCEPTION(ExceptionNotSupported,
							_T("This implementation of pthread doens't create joinable theads")
						);
                        return;
                    default:
						OONET_THROW_EXCEPTION(ExceptionNotSupported,
							_T("Unknown error when trying to join thread")
						);
                        return;
                    }
                }
                // Ok thread joined
                bJoined = true;
                return;
            }
            else
                // No linux implementation for time out
                return _soft_join(tm_timeoutms);
        }

        // Stops the calling thread for a period of time
        void Thread::sleep(ulong tm_sleepms) throw(Exception)
        {	int err;
			err = usleep( tm_sleepms * 1000);		// Unix usleep gets microseconds
			if (err == EINTR)
				OONET_THROW_EXCEPTION(ExceptionInterrupted,
					_T("Thread::Sleep() Action interrupted by a singal!")
					);
        }

	};	// !MT namespace
};	// !OONet namespace
