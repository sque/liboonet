/**
@file MutexPosix.cpp
@brief Implementation of Mutex class on Win32 Platform
*/
#include "./mutex.hpp"

namespace OONet
{
	namespace MT
	{
		// Constructor
		Mutex::Mutex()
		{
			hMutex = CreateMutex(NULL,	// No special Access Rights
				FALSE,					// Don't lock it at the initialization
				NULL					// Unamed mutex
			);
			// Check if mutex created succesfully
			if (hMutex == NULL)
				OONET_THROW_EXCEPTION(ExceptionSystemError,
					"Unknown error trying to create mutex!");
		}


		Mutex::~Mutex()
		{
			// Abandon mutex
			CloseHandle(hMutex);
		}

		void Mutex::unlock() throw(Exception)
		{	// Release mutex
			if (0 == ReleaseMutex(hMutex))
				OONET_THROW_EXCEPTION(ExceptionSystemError, "Unable to unlock mutex!");
		}

		void Mutex::lock(ulong tm_timeoutms) throw(Exception)
		{	DWORD dwResult;

			// Wait for locking
			dwResult = WaitForSingleObject(hMutex, tm_timeoutms);

			// Check error
			if (dwResult == WAIT_TIMEOUT)
				OONET_THROW_EXCEPTION(ExceptionTimeOut,
					"TimeOut waiting to lock mutex!");
			else if (dwResult != WAIT_OBJECT_0)
				OONET_THROW_EXCEPTION(ExceptionSystemError,
					"Unable to lock mutex!");
		}
	}; // !MT namespace
};	// !OONet namespace
