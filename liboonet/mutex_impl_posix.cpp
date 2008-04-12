/**
@file mutex_impl_posix.cpp
@brief Implementation of mutex class on Posix Platform
*/
#include "./mutex.hpp"

namespace oonet
{
	namespace mt
	{
		// Constructor
		mutex::mutex()
		{
			// Create recursive mutex
            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);
            pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

			// From the reference ptrhead_mutex_init always return 0;
			pthread_mutex_init(&mutex_h, &attr);
		}

		// Destructor
		mutex::~mutex()
		{
			// Destroy mutex
			pthread_mutex_destroy(&mutex_h);
		}

		// Mutex unlock
		void mutex::unlock()
		{
			if (0 != pthread_mutex_unlock(&mutex_h))
				OONET_THROW_EXCEPTION(ExceptionSystemError, "Unable to unlock mutex!");
		}

		// Mutex lock
		void mutex::lock(ulong tm_timeoutms)
		{
			// Lock for ever if requested
			if (tm_timeoutms == Infinity)
			{
				if (0 != pthread_mutex_lock(&mutex_h))
					OONET_THROW_EXCEPTION(ExceptionLockError, "Unable to lock mutex!");
				return;
			}

            // Current time
            time_t curTime;
            timespec expireTime;
            time(&curTime);

            // Set expiration time
            expireTime.tv_sec = curTime + (tm_timeoutms /1000);
            expireTime.tv_nsec =  (tm_timeoutms % 1000) * 1000000;

            // Try to lock mutex with a time out
            int ret_error = pthread_mutex_timedlock(&mutex_h, &expireTime);
            if (ret_error == ETIMEDOUT)
            {
                OONET_THROW_EXCEPTION(ExceptionTimeOut,
					"TimeOut waiting to lock mutex!");
            }
            else
            {
                OONET_THROW_EXCEPTION(ExceptionLockError,
					"Unable to lock mutex!");
            }
		}
	}; // !mt namespace
};	// !oonet namespace
