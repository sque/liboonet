/**
@file MutexPosix.cpp
@brief Implementation of Mutex class on Win32 Platform
*/
#include "./mutex.hpp"

namespace oonet
{
	namespace mt
	{
		// Constructor
		mutex::mutex()
		{
			mutex_h = CreateMutex(NULL,	// No special Access Rights
				FALSE,					// Don't lock it at the initialization
				NULL					// Unamed mutex
			);
			// Check if mutex created succesfully
			if (mutex_h == NULL)
				OONET_THROW_EXCEPTION(ExceptionSystemError,
					"Unknown error trying to create mutex!");
		}


		mutex::~mutex()
		{
			// Abandon mutex
			CloseHandle(mutex_h);
		}

		void mutex::unlock()
		{	// Release mutex
			if (0 == ReleaseMutex(mutex_h))
				OONET_THROW_EXCEPTION(ExceptionSystemError, "Unable to unlock mutex!");
		}

		void mutex::lock(ulong tm_timeoutms)
		{	DWORD dwResult;

			// Wait for locking
			dwResult = WaitForSingleObject(mutex_h, tm_timeoutms);

			// Check error
			if (dwResult == WAIT_TIMEOUT)
				OONET_THROW_EXCEPTION(ExceptionTimeOut,
					"TimeOut waiting to lock mutex!");
			else if (dwResult != WAIT_OBJECT_0)
				OONET_THROW_EXCEPTION(ExceptionSystemError,
					"Unable to lock mutex!");
		}
	}; // !mt namespace
};	// !oonet namespace
