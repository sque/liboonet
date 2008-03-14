#ifndef OONET_MT_MUTEX_H_DEFINED
#define OONET_MT_MUTEX_H_DEFINED

#include "OONet.h"
#include "Exception.h"

namespace OONet
{
    namespace MT
    {
    	//! A C++ mutex class
        /**
			Mutex is an easy way to make OOP mutexes. It provides Lock and UnLock functionality
			and works the same in any platform
        */
        class Mutex
        {
        private:
            //! A handle to mutex object that will be used
            MUTEX hMutex;

            // Mutex is uncopiable
            Mutex(const Mutex &r);
            Mutex & operator=(const Mutex & r);

        public:

			//! Constructs mutex object, <b>UNLOCKED</b>
			/**
			@throw ExceptionSystemError Raised if system denied to provide us the mutex.
			*/
            Mutex();

            //! Destructor
            virtual ~Mutex();	// < Destructor

			//! Used to lock mutex for an operation with a time limit.
			/**
				If the object is already locked by another thread, then this function blocks until it can get
				ownership of the object or the specified time has passed.
			@param tm_timeoutms The maximum time to wait until we get ownership of mutex in <b>Milliseconds</b>.
				If MT::Infinity is passed, then it will lock for ever until the other thread unlocks it.
			@throw ExceptionTimeOut Raised when maximum time has passed and we couldn't take ownership of mutex.
			@throw ExceptionSystemError Raised if there was a system error while trying to lock mutex.
			*/
			void lock(ulong tm_timeoutms = Infinity) throw(Exception);

			//! Used to unlock object
            /**
				This function releases the previous captured ownership of the mutex
			@throw ExceptionSystemError Raised if there was a system error while trying to lock mutex.
            */
            void unlock() throw(Exception);
        };	// !Mutex class
    };  // !MT namespace
};	// !OONet namespace

#endif // !OONET_MT_MUTEX_H_DEFINED
