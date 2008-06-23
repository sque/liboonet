/**
@file semaphore_impl_win32.cpp
@brief Implementation of semaphore class on Win32 Platform
*/
#include "./semaphore.hpp"

namespace oonet
{
	namespace mt
	{
        // Win32 counting semaphore implementation
        class semaphore::impl
	    {
        public:
            HANDLE sem_h;   // Semaphore handle
            
            impl(unsigned int init_count = 0)
            {
                sem_h = CreateSemaphore(
                    NULL,
                    init_count, // Initial value to custom
                    255,        // Max count
                    NULL);      // No name
            }

            // Destructor
            ~impl()
            {
  			    // Close Semaphore object
			    CloseHandle(sem_h);
            }

		    // Post (increase counter)
            void post()
            {
                // Increase by one
                ReleaseSemaphore(
                    sem_h,
                    1,      // Increase only by One
                    NULL	// We dont need last value
                    );
            }

            // Wait for a semaphore for predefined time
		    void wait(ulong tm_timeoutms)
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
        };  // !impl class

        // Constructor
        semaphore::semaphore()
            :pimpl(NULL)
        {
            pimpl = new impl();
        }


        // Destructor
        semaphore::semaphore(unsigned int init_count)
            :pimpl(NULL)
        {
            pimpl = new impl(init_count);
        }

        // Destructor
        semaphore::~semaphore()
        {
            if (pimpl != NULL)
                delete pimpl;
        }

		// Post (increase counter)
        void semaphore::post()
        {
            pimpl->post();
        }

        // Wait for a semaphore for predefined time
		void semaphore::wait(ulong tm_timeoutms)
		{
			pimpl->wait(tm_timeoutms);
		}
	}; // !mt namepsace
};	// !oonet namespace
