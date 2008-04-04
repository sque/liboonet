#ifndef OONET_MT_SEMAPHORE_H_INCLUDED
#define OONET_MT_SEMAPHORE_H_INCLUDED

#include "OONet.h"
#include "Exception.h"

namespace OONet
{
    namespace MT
    {
    	//! A C++ semaphore class
    	/**
			Cross-platform C++ semaphore objects.
		*/
        class semaphore
        {
        private:
			//! Handle of system's semaphore
            SEMAPHORE_HANDLE sem_h;

			// Semaphore is NonCopyable
            semaphore(const semaphore &r);
            semaphore & operator=(const semaphore & r);

        public:
            //! Default constructor
            /**
				Creates a semaphore that initially has 0 value.
			*/
            semaphore();

            //! Constructor with custom initial value
            /**
			@param initial The inital value of semaphore
			*/
            explicit semaphore(int initial);

            //! Destructor
            virtual ~semaphore();

            //! Wait for semaphore until someone posts it or a timeout is reached
            /**
				When a semaphore is posted, its value its increased
				by one, every thread that succesfully waits for a Semaphore
				its value is decreased by one. When semaphore has value equal
				to zero, all wait actions are blocked until someone posts it.
			@param tm_timeoutms The maximum time to wait for this semaphore in milliseconds.
			@throw ExceptionTimeOut If the maximum time has passed and the wait on semaphore failed.
			@see post()
			*/
            void wait(ulong tm_timeoutms = Infinity);

            //! Post a semaphore
            /**
				When a sempahore is posted, its internal value is increased by one.
				For every succesfull post() there can be a succesfull wait(). If a thread
				waits for a semaphore, it actually waits for another thread to post() on this
				thread.
			*/
            void post();
        };	// !semaphore class
    }   // !MT namespace
} // !OONet namespace

#endif // OONET_MT_SEMAPHORE_H_INCLUDED
