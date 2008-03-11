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


        // Start Implementation
    #if (OONET_OS == OONET_OS_LINUX)
    #elif (OONET_OS == OONET_OS_WIN32)
        void Thread::_win32_start(void) throw(Exception)
        {
            if (bRunning == true)
            {
                OONET_THROW_EXCEPTION(ExceptionThreadAlreadyStarted,
					"Thread alreay running!"
				);
                return;   // Error thread already started
            }

            // Clear previous handles if exist
            if (hThread != NOTHREAD)
            {
                CloseHandle(hThread);	// Close handle
                hThread = NOTHREAD;		// Mark it unused
            }

            /////////////////
            // Start Thread
            hThread = CreateThread(NULL,	// No security attributes
                0,							// Default stack size
                this->_thread_func,			// The address of the thread procedure
                this,						// A pointer to this object
                0,							// No creation flag
                &ThreadId);					// The thread id

            if (hThread == NULL)
            {
                OONET_THROW_EXCEPTION(ExceptionSystemError,
					"Cannot start thread.."
				);
                return;	// Error on starting the thread
            }

            // Thread started...
            bRunning = true;
            return;		// Thread started succesfully
        }
    #endif


    #if (OONET_OS == OONET_OS_LINUX)
	#elif (OONET_OS == OONET_OS_WIN32)
		void Thread::_win32_join(long ms) throw(Exception)
        {
			DWORD dwResult;
			// Wait for joining
			dwResult = WaitForSingleObject(hThread, ms);

			switch(dwResult)
			{
			case WAIT_TIMEOUT:
				OONET_DEBUG_L2(_T("Thread::_win32_join() time-out!\n"));
				OONET_THROW_EXCEPTION(ExceptionTimeOut,
					"TimeOut waiting to join thread!");
				return;
			case WAIT_OBJECT_0:
				OONET_DEBUG_L2(_T("Thread::_win32_join() succeed!\n"));
				return;
			default:
                OONET_DEBUG_L1(_T("Thread::_win32_join() failed for unknown reason!\n"));
				OONET_THROW_EXCEPTION(ExceptionSystemError, "Unable to join thread!");
			}
		}
    #endif

        void Thread::_soft_join(ulong tm_timeoutms) throw(Exception)
        {   OONET_DEBUG_L2("Thread::_soft_join()_\n");
            // Local variables
            ulong tm_passed;		// A counter for time passed

            // Check every 500 ms the state of Thread
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
                pthis->ThreadRoutine();
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

            // Call OS-specific start code
            try // Wait for possible exceptions
            {
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
//
//        // Stops the calling thread for a period of time
//        void Thread::sleep(long tm_sleepms) throw(Exception)
//        {
//            #if (_OS == OONET_OS_WIN32)
//                ::Sleep( tm_sleepms); 	//Windows sleep gets mseconds
//            #elif (OONET_OS == OONET_OS_LINUX)
//                int err;
//                err = usleep( tm_sleepms * 1000.0);		// Unix sleep gets seconds
//                if (err == EINTR)
//                    OONET_THROW_EXCEPTION(ExceptionInterrupted,
//                        _T("Thread::Sleep() Action interrupted by a singal!")
//                        );
//            #endif
//        }
    };  // !MT namespace
};	// !OONet namespace
