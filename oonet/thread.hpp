#ifndef OONET_MT_THREAD_H_INCLUDED
#define OONET_MT_THREAD_H_INCLUDED

#include "./oonet.hpp"
#include "./scoped_lock.hpp"
#include "./semaphore.hpp"

namespace oonet
{
    namespace mt
    {
		//! A thread abstract class.
        /**
            Thread is used as base class to create threads. The idea is to deriver a class that implements
            the function Thread::thread_routine. When you start the thread, it will create a new thread and
            run Thread::thread_routine at the new one.
        @remarks At the derivered class you should take care of shutting down thread before destroying the
            object, otherwise you'll be at the risk of "pure virtual function was called" error.
        @brief
        */
        class thread : private mutex
        {
        	public:
				OONET_DECLARE_EXCEPTION(ExceptionThreadAlreadyStarted);

				//! Native handle type of thread
				typedef THREAD_HANDLE native_handle_type;

            private:
				// Thread is NonCopiable
				thread(const thread &r);
				thread & operator=(const thread & r);

                //! The handle of the thread
                native_handle_type thread_h;

                //! The thread's Id
                unsigned long thread_id;

                //! A flag if the thread is running
                bool b_running;

                //! A flag if thread has been joined. (Only for linux)
                bool b_joined;

				//! An event to wait for thread to start
				mt::semaphore sem_start_thread;

				//! The dispatcher for calling the appropriate ThreadRoutine
                /**
					When asking from system to create a new thread you must
					provide him with a static member function, this is the one!
					This function will find which object started the thread and
					give controll on his ThreadRoutine function
                @param _caller A pointer to the Thread that was called from.
                @return Always null.
                */
                static THREADPROC_RETURN THREADTYPE _thread_func(void * _caller);

				//! System-specific implementation of Thread::start
                void _system_start(void);

				//! System-specific implemetation of Thread::join
                void _system_join(ulong tm_timeoutms);

				//! A software join implementation.
                /**
					This is a fallback function for joining if system doesn't provide
					a nice mechanism to do that. This function has a drawback that
					it works with pooling algorithm, so there is limit on the time
					needed to responce when join is possible. The lower the this time
					is the more pool per seconds are required and thus more cpu usage.
                 @param tm_timeoutms The maximum time to wait for caller to join.
                 */
                void _soft_join(ulong tm_timeoutms);

            protected:

				//! The thread's basic routine.
                /**
					Here you must put all the code that the thread will do.
					This is the core of the thread, everything works, to run this
					function at new thread ;)
                */
                virtual void operator()() = 0;

            public:

				//! Contructor of Thread, It does <b>NOT</b> start the thread
                /**
					It initializes all the values and prepares the object so
					that you can call start()
                */
                thread();

                /**
                * You should kill object at the deriverd desctructor before reaching
                * this point.
                * @brief Destructor of thread, it tries to kill the thread.
                */
                virtual ~thread();

                //! Check if the thread is running.
                inline bool running() const
                {   return b_running; }

				//! Join with this thread in a predefined maximum time.
                /**
					This function does <b>NOT</b> tries to stop the thread, it just waits
					until the thread has stopped or the maximume time is reached
                @param tm_timeoutms The maximum time in milliseconds to wait until the thread is finished
					or pass Thread::Infinity to lock for ever until the thread stops.
				@throw ExceptionNotSupported If this systems implementation doesn't support joinable threads.
				@throw ExceptionTimeOut If maximum time has been reached and the thread hasn't stopped yet.
                */
                void join(ulong tm_timeoutms = Infinity);

				//! Start the thread
                /**
					It will create a new thread and run the Thread::ThreadRoutine
					(in a controllable safe-way) at the new created thread.
				@throw ExceptionThreadAlreadyStarted If the thread is already started.
				@throw ExceptionSystemError If there was an internal system error while starting thread.
                */
                void start();

                //! It sleeps the <b>CALLING</b> thread for a period of time.
                /**
					It will suspend the execution of the current thread for
					defined time. It is a static function and can be called
					from everywhere without instantiating any object.
                @param tm_sleepms The amount of time in milliseconds that the thread will be suspended.
                @throw ExceptionInterrupted If the suspension of thread was interrupt by another thread.
                */
                static void sleep(ulong tm_sleepms);

				//! Returns the system thread handle of this thread.
                /**
					The return value type, varies from platform to platform, so take care
					for cross-platform probs.
                */
                native_handle_type get_thread_handle()
                {   return thread_h; }

        };  // Thread class
    };  // mt namespace
};	// !oonet namespace

#endif // !OONET_MT_THREAD_H_INCLUDED
