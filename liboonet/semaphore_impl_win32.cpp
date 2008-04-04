/**
@file SemaphorePosix.cpp
@brief Implementation of Semaphore class on Win32 Platform
*/
#include "Semaphore.h"

namespace OONet
{
	namespace MT
	{
        // Constructor
        Semaphore::Semaphore()
        {
            semHandle = CreateSemaphore(
                NULL,
                0,      // Initial value to 0
                255,    // Max count
                NULL);  // No name
        }


        Semaphore::Semaphore(int initial)
        {
            semHandle = CreateSemaphore(
                NULL,
                initial,// Initial value to custom
                255,    // Max count
                NULL);  // No name
        }

        // Destructor
        Semaphore::~Semaphore()
        {
  			// Close Semaphore object
			CloseHandle(semHandle);
        }

		// Post (increase counter)
        void Semaphore::post()
        {
            // Increase by one
            ReleaseSemaphore(
                semHandle,
                1,      // Increase only by One
                NULL	// We dont need last value
                );
        }

        // Wait for a semaphore for predefined time
		void Semaphore::wait(ulong tm_timeoutms)
		{	DWORD dwResult;
			
			// Wait for locking
			dwResult = WaitForSingleObject(semHandle, tm_timeoutms);

			// Check error
			if (dwResult == WAIT_TIMEOUT)
				OONET_THROW_EXCEPTION(ExceptionTimeOut, 
					"Semaphore was abandoned");
			else if (dwResult != WAIT_OBJECT_0)
				OONET_THROW_EXCEPTION(ExceptionSystemError, 
					"Unable to wait for semaphore!");

		}
	}; // !MT namepsace
};	// !OONet namespace
