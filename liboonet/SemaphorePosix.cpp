/**
@file SemaphorePosix.cpp
@brief Implementation of Semaphore class on Posix Platform
*/
#include "Semaphore.h"

namespace OONet
{
	namespace MT
	{
        // Constructor
        Semaphore::Semaphore()
        {
            sem_init(&semHandle,
                0,  // Not process-shared
                0); // Initial value to 0
        }


        Semaphore::Semaphore(int initial)
        {
            sem_init(&semHandle,
                0,          // Not process-shared
                initial);   // Initial value to custom
        }

        // Destructor
        Semaphore::~Semaphore()
        {
            // Destroy semaphore
            sem_destroy(&semHandle);
        }

		// Post (increase counter)
        void Semaphore::post()
        {
            sem_post(&semHandle);
        }

        // Wait for a semaphore for predefined time
		void Semaphore::wait(ulong tm_timeoutms)
		{
			// Wait for infinity
			if (tm_timeoutms == Infinity)
			{
				sem_wait(&semHandle);
				return;
			}

            // Current time
            time_t curTime;
            timespec expireTime;
            time(&curTime);

            // Set expiration time
            expireTime.tv_sec = curTime + (tm_timeoutms /1000);
            expireTime.tv_nsec =  (tm_timeoutms % 1000) * 1000000;

            // Try to time out sema
            if ((0 != sem_timedwait(&semHandle, &expireTime))
                &&  (errno == ETIMEDOUT))
                OONET_THROW_EXCEPTION(ExceptionTimeOut, "Semaphore was abandoned");

		}
	}; // !MT namepsace
};	// !OONet namespace
