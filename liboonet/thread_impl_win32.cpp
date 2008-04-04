/**
@file ThreadPosix.cpp
@brief Implementation of Thread class on Win32 Platform
*/
#include "Thread.h"

namespace OONet
{
	namespace MT
	{
        void Thread::_system_start(void) throw(Exception)
        {
			if (bRunning == true)
            {
                OONET_THROW_EXCEPTION(ExceptionThreadAlreadyStarted,
					"Thread alreay running!"
				);
                return;   // Error thread already started
            }

            // Clear previous handles if exist
            if (hThread != 0)
            {
                CloseHandle(hThread);	// Close handle
                hThread = 0;			// Mark it unused
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

        void Thread::_system_join(ulong tm_timeoutms) throw(Exception)
        {   OONET_DEBUG_L2("Thread::_win32_join()_\n");

            DWORD dwResult;
			// Wait for joining
			dwResult = WaitForSingleObject(hThread, tm_timeoutms);

			switch(dwResult)
			{
			case WAIT_TIMEOUT:
				OONET_DEBUG_L2("Thread::_win32_join() time-out!\n");
				OONET_THROW_EXCEPTION(ExceptionTimeOut,
					"TimeOut waiting to join thread!");
				return;
			case WAIT_OBJECT_0:
				OONET_DEBUG_L2("Thread::_win32_join() succeed!\n");
				return;
			default:
                OONET_DEBUG_L1("Thread::_win32_join() failed for unknown reason!\n");
				OONET_THROW_EXCEPTION(ExceptionSystemError, 
					"Unable to join thread!");
			}
        }

        // Stops the calling thread for a period of time
        void Thread::sleep(ulong tm_sleepms) throw(Exception)
        {	
			::Sleep( tm_sleepms); 	//Windows sleep gets mseconds
        }

	};	// !MT namespace
};	// !OONet namespace
