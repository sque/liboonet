/**
@file semaphore_impl_posix.cpp
@brief Implementation of semaphore class on Posix Platform
*/
#include "./semaphore.hpp"

namespace oonet
{
	namespace mt
	{
	    // POSIX Internal Implementation
	    class semaphore::impl
	    {
        public:
            // Posix semaphore handle
			sem_t sem_h;

            // Default constructor (Initialize counter to zero)
	        impl(int init_count = 0)
	        {
                if (-1 == sem_init(&sem_h,
                    0,  // Not process-shared
                    init_count) // Initial value to 0
                )
                {
                    OONET_THROW_EXCEPTION(ExceptionSystemError,
                        "Unable to create semaphore!");
                }
	        }

	        // Destructor
	        ~impl()
	        {
	            // Destroy semaphore
                sem_destroy(&sem_h);
	        }

	        void post()
	        {
	            sem_post(&sem_h);
	        }

	        void wait(ulong tm_timeoutms)
	        {
	            // Wait for infinity
                if (tm_timeoutms == Infinity)
                {
                    sem_wait(&sem_h);
                    return;
                }

#if ((_POSIX_C_SOURCE >= 200112L) || (_XOPEN_SOURCE >= 600))
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

#else
                ulong tm_waited_ms = 0;
                // The resolution clock will not be so good
                while(sem_trywait(&sem_h) != 0)
                {   printf("errorno on sem_timedway %d and EAGAIN: %d\n", errno, EAGAIN);

                    usleep(10000);  // 10 Miliseconds
                    tm_waited_ms += 10;
                    if (tm_waited_ms > tm_timeoutms)
                    {   // Time out
                        OONET_THROW_EXCEPTION(ExceptionTimeOut,
                            "Semaphore was abandoned");
                    }
                }
#endif
	        }
	    };

        // Constructor
        semaphore::semaphore()
            :pimpl(NULL)
        {
            pimpl = new impl();
        }


        // Destructor
        semaphore::semaphore(int init_count)
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
	}; // !MT namepsace
};	// !oonet namespace
