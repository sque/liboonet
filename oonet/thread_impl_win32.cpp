/**
@file thread_impl_win32.cpp
@brief Implementation of thread class on Win32 Platform
*/
#include "./thread.hpp"

namespace oonet
{
	namespace mt
	{
        void thread::_system_start(void)
        {
			if (b_running == true)
            {
                OONET_THROW_EXCEPTION(ExceptionThreadAlreadyStarted,
					"Thread alreay running!"
				);
                return;   // Error thread already started
            }

            // Clear previous handles if exist
            if (thread_h != 0)
            {
                CloseHandle(thread_h);	// Close handle
                thread_h = 0;			// Mark it unused
            }

            /////////////////
            // Start Thread
            thread_h = CreateThread(NULL,	// No security attributes
                0,							// Default stack size
                this->_thread_func,			// The address of the thread procedure
                this,						// A pointer to this object
                0,							// No creation flag
				&thread_id);					// The thread id

            if (thread_h == NULL)
            {
                OONET_THROW_EXCEPTION(ExceptionSystemError,
					"Cannot start thread.."
				);
                return;	// Error on starting the thread
            }

            // Thread started...
            b_running = true;
            return;		// Thread started succesfully
        }

        void thread::_system_join(ulong tm_timeoutms)
        {	DWORD dwResult;
			// Wait for joining
			dwResult = WaitForSingleObject(thread_h, tm_timeoutms);

			switch(dwResult)
			{
			case WAIT_TIMEOUT:
				OONET_THROW_EXCEPTION(ExceptionTimeOut,
					"TimeOut waiting to join thread!");
				return;
			case WAIT_OBJECT_0:
				return;
			default:
				OONET_THROW_EXCEPTION(ExceptionSystemError, 
					"Unable to join thread!");
			}
        }

        // Stops the calling thread for a period of time
        void thread::sleep(ulong tm_sleepms)
        {	
			::Sleep( tm_sleepms); 	//Windows sleep gets mseconds
        }

	};	// !mt namespace
};	// !oonet namespace
