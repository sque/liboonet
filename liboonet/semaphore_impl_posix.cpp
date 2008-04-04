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
        semaphore::semaphore()
        {
            sem_init(&sem_h,
                0,  // Not process-shared
                0); // Initial value to 0
        }


        semaphore::semaphore(int initial)
        {
            sem_init(&sem_h,
                0,          // Not process-shared
                initial);   // Initial value to custom
        }

        // Destructor
        semaphore::~semaphore()
        {
            // Destroy semaphore
            sem_destroy(&sem_h);
        }

		// Post (increase counter)
        void semaphore::post()
        {
            sem_post(&sem_h);
        }

        // Wait for a semaphore for predefined time
		void semaphore::wait(ulong tm_timeoutms)
		{
			// Wait for infinity
			if (tm_timeoutms == Infinity)
			{
				sem_wait(&sem_h);
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
            if ((0 != sem_timedwait(&sem_h, &expireTime))
                &&  (errno == ETIMEDOUT))
                OONET_THROW_EXCEPTION(ExceptionTimeOut, "Semaphore was abandoned");

		}
	}; // !MT namepsace
};	// !OONet namespace
