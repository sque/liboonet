/**
 @file Mutex.cpp
 @brief Implementation of Mutex class
 */

#include "./Mutex.h"
#include <iostream>

namespace Slib
{
	namespace MT
	{

		//////////////////////////////////////////////////////////////////////
		// Construction/Destruction
		//////////////////////////////////////////////////////////////////////

		Mutex::Mutex()
		{
			// Create a mutex for this object
		#if (SLIB_OS == SLIB_OS_WIN32)
			hMutex = CreateMutex(NULL,	// No special Access Rights
				FALSE,					// Don't lock it at the initialization
				NULL					// Unamed mutex
			);
			// Check if mutex created succesfully
			if (hMutex == NULL)
				SLIB_THROW_EXCEPTION(ExceptionSystemError,
					"Unknown error trying to create mutex!");

		#elif (SLIB_OS == SLIB_OS_LINUX)

            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);
            pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

			// From the reference ptrhead_mutex_init always return 0;
			pthread_mutex_init(&hMutex, &attr);
		#endif
		}


		Mutex::~Mutex()
		{
			// Destroy mutex
		#if (SLIB_OS == SLIB_OS_WIN32)
			CloseHandle(hMutex);
		#elif (SLIB_OS == SLIB_OS_LINUX)
			pthread_mutex_destroy(&hMutex);
		#endif
		}

		/////////////////////////////
		// Lock & Unlock functions //
		/////////////////////////////
		void Mutex::lock() throw(Exception)
		{
			// Wait until the thread signals the mutex
		#if (SLIB_OS == SLIB_OS_WIN32)
			if (WAIT_OBJECT_0 != WaitForSingleObject(hMutex, INFINITE))
				SLIB_THROW_EXCEPTION(ExceptionSystemError,
					"Unable to lock mutex!");
		#elif (SLIB_OS == SLIB_OS_LINUX)
			if (0 != pthread_mutex_lock(&hMutex))
				SLIB_THROW_EXCEPTION(ExceptionSystemError, "Unable to lock mutex!");
		#endif
		}

		void Mutex::unlock() throw(Exception)
		{
			// No more neeading the mutex
		#if (SLIB_OS == SLIB_OS_WIN32)
			ReleaseMutex(hMutex);
		#elif (SLIB_OS == SLIB_OS_LINUX)
			if (0 != pthread_mutex_unlock(&hMutex))
				SLIB_THROW_EXCEPTION(ExceptionSystemError, "Unable to unlock mutex!");
		#endif
		}

		void Mutex::lock(ulong tm_timeoutms) throw(Exception)
		{
			// Wait until the thread signals the mutex
		#if (SLIB_OS == SLIB_OS_WIN32)
			DWORD dwResult;
			// Wait for locking
			dwResult = WaitForSingleObject(hMutex, dwTimeOutMs);

			// Check error
			if (dwResult == WAIT_TIMEOUT)
				SLIB_THROW_EXCEPTION(ExceptionTimeOut,
					"TimeOut waiting to lock mutex!");
			else if (dwResult != WAIT_OBJECT_0)
				SLIB_THROW_EXCEPTION(ExceptionSystemError,
					"Unable to lock mutex!");
		#elif (SLIB_OS == SLIB_OS_LINUX)
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
                SLIB_THROW_EXCEPTION(ExceptionTimeOut, _T("TimeOute waiting to lock mutex!)"));
            }
            else
            {
                SLIB_THROW_EXCEPTION(ExceptionSystemError,
					_T("Unable to lock mutex!"));
            }
		#endif
		}
	}; //! MT namespace
};	//! Slib namespace
