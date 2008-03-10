/**
@file MutexPosix.cpp
@brief Implementation of Mutex class on Posix Platform
*/
#include "Mutex.h"
#include <iostream>

namespace OONet
{
	namespace MT
	{
		// Constructor
		Mutex::Mutex()
		{
			// Create recursive mutex
            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);
            pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

			// From the reference ptrhead_mutex_init always return 0;
			pthread_mutex_init(&hMutex, &attr);
		}


		Mutex::~Mutex()
		{
			// Destroy mutex
			pthread_mutex_destroy(&hMutex);
		}

		void Mutex::unlock() throw(Exception)
		{
			if (0 != pthread_mutex_unlock(&hMutex))
				OONET_THROW_EXCEPTION(ExceptionSystemError, "Unable to unlock mutex!");
		}

		void Mutex::lock(ulong tm_timeoutms) throw(Exception)
		{
			// Lock for ever if requested
			if (tm_timeoutms == Infinity)
			{
				if (0 != pthread_mutex_lock(&hMutex))
					OONET_THROW_EXCEPTION(ExceptionSystemError, "Unable to lock mutex!");
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
            int ret_error = pthread_mutex_timedlock(&hMutex, &expireTime);
            if (ret_error == ETIMEDOUT)
            {
                OONET_THROW_EXCEPTION(ExceptionTimeOut, _T("TimeOute waiting to lock mutex!)"));
            }
            else
            {
                OONET_THROW_EXCEPTION(ExceptionSystemError,
					_T("Unable to lock mutex!"));
            }
		}
	}; // !MT namespace
};	// !OONet namespace
