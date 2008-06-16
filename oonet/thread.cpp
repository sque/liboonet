/**
 @file thread.cpp
 @brief Implementation of general functions of thread class.
 */

#include "./thread.hpp"

namespace oonet
{
    namespace mt
    {
        /////////////////////////////////
        // OS-Independant -> OS-Specific
        // NOTHREAD
    #if (OONET_OS == OONET_OS_WIN32)
        #define NOTHREAD NULL
    #elif ((OONET_OS == OONET_OS_LINUX) || (OONET_OS == OONET_OS_OSX))
        #define NOTHREAD 0
    #endif

        void thread::_soft_join(ulong tm_timeoutms)
        {
            // Local variables
            ulong tm_passed;		// A counter for time passed

            // Check every 250 ms the state of Thread
			for(tm_passed = 0;(tm_passed <  tm_timeoutms) || (tm_timeoutms == Infinity); tm_passed+= 250)
            {
                // If thread stopped exit
                if (!b_running)
                    return;

                // Else wait one step more
                thread::sleep(250);
            }

            // time out reached
			OONET_THROW_EXCEPTION(ExceptionTimeOut,
				"TimeOut waiting to join thread!");
        }


        // Thread real fuction
        THREADPROC_RETURN THREADTYPE thread::_thread_func(void * _caller)
        {
            thread * pthis = (thread *)_caller;

			// Ok we started
			pthis->sem_start_thread.post();
			try
			{
                (*pthis)();
			}
            catch(std::exception)
            {}

            // To lock exei noima giati to bRunning mporei na tropopoihthei apo allo thread
            {scoped_lock tmp_lock(*pthis);

				pthis->b_running = false;
            }
            return NULL;
        }

        // Constructor of thread
        thread::thread()
        {
            // Initiliaze variables
            thread_h = NOTHREAD;		// No handle at startup
            b_running = false;			// Thread hasn't start yet
            b_joined = false;			// Thread hasn't joined yet
        }


        // Destructor of thread
        thread::~thread()
        {
            // Join with thread
            join(Infinity);
        }

        // Wait a specific amount of time to see if thread was stopped
        void thread::join(ulong tm_timeoutms)
        {
            // Skip join if we never started thread
            if (thread_h == NOTHREAD)
			{	return;		}

			return _system_join(tm_timeoutms);
        }

        // Start the thread
        void thread::start()
        {
			scoped_lock tmp_lock(*this);	// Lock object for single use

			// Start it
			_system_start();

			// Wait for thread to start
			sem_start_thread.wait();

            return;
        }
    };  // !mt namespace
};	// !oonet namespace
