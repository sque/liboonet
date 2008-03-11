#include "./Semaphore.h"

namespace OONet
{
    namespace MT
    {

        // Constructor
        Semaphore::Semaphore()
        {
#if (SLIB_OS == SLIB_OS_LINUX)
            sem_init(&semHandle,
                0,  // Not process-shared
                0); // Initial value to 0
#elif (SLIB_OS == SLIB_OS_WIN32)
            semHandle = CreateSemaphore(
                NULL,
                0,      // Initial value to 0
                255,    // Max count
                NULL);  // No name
#endif
        }

        Semaphore::Semaphore(int initial)
        {
#if (SLIB_OS == SLIB_OS_LINUX)
            sem_init(&semHandle,
                0,          // Not process-shared
                initial);   // Initial value to custom
#elif (SLIB_OS == SLIB_OS_WIN32)
            semHandle = CreateSemaphore(
                NULL,
                initial,// Initial value to custom
                255,    // Max count
                NULL);  // No name
#endif
        }
        // Destructor
        Semaphore::~Semaphore()
        {
            // Destroy semaphore
#if (SLIB_OS == SLIB_OS_LINUX)
            sem_destroy(&semHandle);
#elif (SLIB_OS == SLIB_OS_WIN32)
			// Close Semaphore object
			CloseHandle(semHandle);
#endif
        }

        // Post (increase counter)
        void Semaphore::Post()
        {
#if (SLIB_OS == SLIB_OS_LINUX)
            sem_post(&semHandle);
#elif (SLIB_OS == SLIB_OS_WIN32)
            // Increase by one
            ReleaseSemaphore(
                semHandle,
                1,      // Increase only by One
                NULL   // We dont need last value
                );
#endif
        }

        // Wait for semaphore
        void Semaphore::wait()
        {
#if (SLIB_OS == SLIB_OS_LINUX)
            sem_wait(&semHandle);
#elif (SLIB_OS == SLIB_OS_WIN32)
            WaitForSingleObject(semHandle, INFINITE);
#endif
        }

		// Wait for a semaphore for predefined time
		void Semaphore::Wait(ulong tm_timeoutms)
		{
		#if (SLIB_OS == SLIB_OS_LINUX)
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
                SLIB_THROW_EXCEPTION(ExceptionTimeOut, _T("Semaphore was abandoned"));

		#elif (SLIB_OS == SLIB_OS_WIN32)
			if (WAIT_OBJECT_0 != WaitForSingleObject(semHandle, tm_timeoutms))
				SLIB_THROW_EXCEPTION(ExceptionTimeOut, "Semaphore was abandoned");
		#endif
		}

    };
};	// !OONet
