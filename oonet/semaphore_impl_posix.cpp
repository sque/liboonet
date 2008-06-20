/**
@file semaphore_impl_posix.cpp
@brief Implementation of semaphore class on Posix Platform
*/
#include "./semaphore.hpp"
#include "./scoped_lock.hpp"

namespace oonet
{
	namespace mt
	{
	    unsigned long sem_count_id = 0;

	    // POSIX Internal Implementation with named semaphores
	    class semaphore::impl
	    {
        public:

            // Posix semaphore handle
			sem_t sem_h;

			// Pointer to semaphore handle
			sem_t * sem_ph;

#if defined(__APPLE__)
            ////////////////////////////////////////////////////////
            // On apple OSX posix implementation does not support unnamed sockets,
			// so here we are unnamed sockets over named!

			// Unique name of this named semaphore
			char unique_name[256];

            // Default constructor (Initialize counter to zero)
	        impl(unsigned int init_count = 0)
				:sem_ph(&sem_h)
	        {	// Create a unique name
                sprintf(unique_name, "/tmp/oonet/%05lu/%lu", getpid(), sem_count_id++);

                // Delete if any previous
                sem_unlink(unique_name);

                // Create a new one
                if (SEM_FAILED == (sem_ph = sem_open(unique_name,
                    O_EXCL | O_CREAT,   // Create new one
                    600,                // We dont want to be accesible from other processes
                    init_count))        // Initial count name
                )
                {
                    OONET_THROW_EXCEPTION(ExceptionSystemError,
                        "Unable to create semaphore!");
                }
	        }

	        // Destructor
	        ~impl()
	        {
	            // Close connection to semaphore
                sem_close(sem_ph);
                
				// Delete it too
                sem_unlink(unique_name);
	        }
#else   // Using unnamed posix native unamed counting semaphores

            // Default constructor (Initialize counter to zero)
	        impl(unsigned int init_count = 0)
				:sem_ph(&sem_h)
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
                sem_destroy(sem_ph);
	        }

#endif
	        void post()
	        {
	            if (sem_post(sem_ph) != 0)
	            {
                    OONET_THROW_EXCEPTION(ExceptionSystemError,
                        "Unable to post on semaphore!");
	            }
	        }

	        void wait(ulong tm_timeoutms)
	        {
	            // Wait for infinity
                if (tm_timeoutms == Infinity)
                {
                    if (sem_wait(sem_ph) != 0)
                    {
                        //print_current_status("Error on sem_post");
                        OONET_THROW_EXCEPTION(ExceptionSystemError,
                            "Unable to post on semaphore!");
                    }
                    return;
                }

// ! Check if we support timeout variant  posix functions
#if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS - 200112L) >= 0
                // Current time
                time_t curTime;
                timespec expireTime;
                time(&curTime);

                // Set expiration time
                expireTime.tv_sec = curTime + (tm_timeoutms /1000);
                expireTime.tv_nsec =  (tm_timeoutms % 1000) * 1000000;

                // Try to time out sema
                if ((0 != sem_timedwait(sem_ph, &expireTime))
                    &&  (errno == ETIMEDOUT))
                    OONET_THROW_EXCEPTION(ExceptionTimeOut, "Semaphore was abandoned");

#else
                ulong tm_waited_ms = 0;
                // The resolution clock will not be so good
                while(sem_trywait(sem_ph) != 0)
                {
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
