/**
@file SemaphorePosix.cpp
@brief Implementation of Semaphore class on Win32 Platform
*/
#include "./semaphore.hpp"

namespace oonet
{
	namespace mt
	{
        // Constructor
        semaphore::semaphore()
        {
            sem_h = CreateSemaphore(
                NULL,
                0,      // Initial value to 0
                255,    // Max count
                NULL);  // No name
        }


        semaphore::semaphore(int initial)
        {
            sem_h = CreateSemaphore(
                NULL,
                initial,// Initial value to custom
                255,    // Max count
                NULL);  // No name
        }

        // Destructor
        semaphore::~semaphore()
        {
  			// Close Semaphore object
			CloseHandle(sem_h);
        }

		// Post (increase counter)
        void semaphore::post()
        {
            // Increase by one
            ReleaseSemaphore(
                sem_h,
                1,      // Increase only by One
                NULL	// We dont need last value
                );
        }

        // Wait for a semaphore for predefined time
		void semaphore::wait(ulong tm_timeoutms)
		{	DWORD dwResult;
			
			// Wait for locking
			dwResult = WaitForSingleObject(sem_h, tm_timeoutms);

			// Check error
			if (dwResult == WAIT_TIMEOUT)
				OONET_THROW_EXCEPTION(ExceptionTimeOut, 
					"Semaphore was abandoned");
			else if (dwResult != WAIT_OBJECT_0)
				OONET_THROW_EXCEPTION(ExceptionSystemError, 
					"Unable to wait for semaphore!");

		}
	}; // !mt namepsace
};	// !oonet namespace
