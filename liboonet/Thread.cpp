/**
 @file Thread.cpp
 @brief Implementation of general functions of Thread class.
 */

#include "./Thread.h"

namespace OONet
{
    namespace MT
    {
        /////////////////////////////////
        // OS-Independant -> OS-Specific
        // NOTHREAD
    #if (OONET_OS == OONET_OS_WIN32)
        #define NOTHREAD NULL
    #elif (OONET_OS == OONET_OS_LINUX)
        #define NOTHREAD 0
    #endif

        void Thread::_soft_join(ulong tm_timeoutms) throw(Exception)
        {   OONET_DEBUG_L2("Thread::_soft_join()_\n");
            // Local variables
            ulong tm_passed;		// A counter for time passed

            // Check every 250 ms the state of Thread
			for(tm_passed = 0;(tm_passed <  tm_timeoutms) || (tm_timeoutms == Infinity); tm_passed+= 250)
            {
                // If thread stopped exit
                if (!bRunning)
                    return;

                // Else wait one step more
                Thread::sleep(250);
            }

            // time out reached
			OONET_THROW_EXCEPTION(ExceptionTimeOut,
				"TimeOut waiting to join thread!");
        }


        // Thread real fuction
        THREADPROC_RETURN THREADTYPE Thread::_thread_func(void * _caller)
        {
            Thread * pthis = (Thread *)_caller;

			// Ok we started
			pthis->semStartThread.post();
			try
			{
                pthis->thread_routine();
			}
            catch(std::exception)
            {   OONET_DEBUG_L1(_T("Thread::_thread_func() exception was thrown from thread!\n"));    }

            // To lock exei noima giati to bRunning mporei na tropopoihthei apo allo thread
            pthis->lock();
            pthis->bRunning = false;
            pthis->unlock();
            return NULL;
        }

        // Constructor of thread
        Thread::Thread()
        {
            // Initiliaze variables
            hThread = NOTHREAD;					// No handle at startup
            bRunning = false;					// Thread hasn't start yet
            bJoined = false;                    // Thread hasn't joined yet
        }


        // Destructor of thread
        Thread::~Thread()
        {
            // Join with thread
            join(Infinity);
        }



        // Wait a specific amount of time to see if thread was stopped
        void Thread::join(ulong tm_timeoutms) throw(Exception)
        {
            // Skip join if we never started thread
            if (hThread == NOTHREAD)
			{   OONET_DEBUG_L2(_T("Thread::Join() skipping we don't have handle\n"));
				return;
			}

			return _system_join(tm_timeoutms);
        }

        // Start the thread
        void Thread::start() throw(Exception)
        {
            lock();		// Lock object for single use


            try // Wait for possible exceptions
            {
            	// Start it
                _system_start();
				// Wait for thread to start
				semStartThread.wait();
            }
            catch(std::exception)
            {
				// Oups
                unlock();   // Unlock before exiting
                throw;		// Forward exception
            }
            unlock();
            return;
        }
    };  // !MT namespace
};	// !OONet namespace
