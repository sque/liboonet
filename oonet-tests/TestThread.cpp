#include "TestThread.h"
#include "Thread.h"
#include <time.h>

namespace OONet
{
	static TestThread theTestThread;

	// Global variables for thread
	bool ThreadRunned;
	int threadCount;

	// Throw a thread
	class SimpleThread : public MT::Thread
	{
	public:
		~SimpleThread()
		{
		    join(MT::Infinity);
            threadCount --;
		}
		protected:
			// Implement run
			virtual void thread_routine(void)
			{
				ThreadRunned = true;
				threadCount ++;
			}

	};

	// A thread for blocking infinitly
	class BlockThread : public MT::Thread
	{
    protected:
        bool bPlay, bUsed;
		MT::Semaphore sema;
	public:
        BlockThread()
        {
            bPlay = false;
        }

		~BlockThread()
		{
			sema.wait();
			bPlay = false;
			threadCount --;
            join(MT::Infinity);
		}
		protected:
			// Implement run
			virtual void thread_routine(void)
			{
			    bPlay = true;
				ThreadRunned = true;
				sema.post();
				while(bPlay)
					sleep(100);
			}

	};

	// A thread for blocking infinitly
	class KillThread : public MT::Thread
	{
	public:
		~KillThread()
		{
			threadCount --;
		}
		protected:
			// Implement run
			virtual void thread_routine(void)
			{
				ThreadRunned = true;
				join();	// kill from the same thread
			}
	};

	// Sub tests implementation
	bool TestThread::TestCtor::OnExecute()
	{	SimpleThread myThread;

		ThreadRunned = false;

		myThread.start();
		MT::Thread::sleep(1000);	// Wait for 3 seconds

		return ThreadRunned;
	}

	// Sub tests implementation
	bool TestThread::TestSpam100::OnExecute()
	{	SimpleThread *myThread[100];
        int spawnedthreads = 100;
		bool bRes = true;

		threadCount = 0;
		ThreadRunned = false;

		// Create 100 threads
		for(int i = 0;i < spawnedthreads;i++)
			myThread[i] = new SimpleThread();

		// Start the threads
		for(int i = 0;i < spawnedthreads;i++)
		{
			myThread[i]->start();
		}

		// Wait to finish
		for(int i = 0;i < spawnedthreads;i++)
		{

			myThread[i]->join(MT::Infinity);
		}

		if (threadCount != spawnedthreads)
			bRes = false;

		// Delete threads
		for(int i = 0;i < spawnedthreads;i++)
		{
			delete myThread[i];
		}

		return bRes;
	}


	bool TestThread::TestSleepAccuracy::OnExecute()
	{	time_t startT, endT;
		long timediff, testtime = 5;

		time(&startT);
		MT::Thread::sleep(testtime * 1000);
		time(&endT);

		timediff = (long)(endT - startT);

		if ((timediff <(testtime - 1)) || ((testtime + 1) < timediff))
			return false;

		return true;
	}

	bool TestThread::TestJoinTimeout::OnExecute()
	{
		BlockThread bThread;
		bThread.start();
		bThread.join(3000);

		return false;
	}

	bool TestThread::TestJoinQuality::OnExecute()
	{
		SimpleThread bThread;
		bThread.start();

		// Try twice to join
		bThread.join(MT::Infinity);
        if (bThread.running())
			return false;
		bThread.join(MT::Infinity);
		if (bThread.running())
            return false;

		return true;
	}

	bool TestThread::TestBug1::OnExecute()
	{
		SimpleThread * pThread = new SimpleThread;
		delete pThread;
		return true;
	}

	bool TestThread::TestKill::OnExecute()
	{

		BlockThread  bThread;

#if (OONET_OS == OONET_OS_WIN32)
		HANDLE hOrigThread, hThread;

		bThread.start();
		// Get Handle and duplicate it
		hOrigThread = bThread.get_thread_handle();
		DuplicateHandle(
		  GetCurrentProcess(),
		  hOrigThread,
		  GetCurrentProcess(),
		  &hThread,
		  0,
		  TRUE,
		  DUPLICATE_SAME_ACCESS);
#endif
		// Kill it
		MT::Thread::sleep(1000);

#if (OONET_OS == OONET_OS_WIN32)
		// Check if stopped
		DWORD dwExitCode = 0;
		if (! GetExitCodeThread(hThread, &dwExitCode))
		{
			_tprintf(_T("%s"), GetSystemLastErrorDescription().c_str());
			return false;
		}

		if (dwExitCode == STILL_ACTIVE)
			return false;
  #endif
		return true;
	}

	bool TestThread::TestFastSpam100::OnExecute()
	{	BlockThread *pThread[100];

		// Start all together
		for(int i = 0;i < 100;i++)
		{
			pThread[i] = new BlockThread();
			pThread[i]->start();
			delete pThread[i];
		}

		return true;
	}

	bool TestThread::TestDoubleStart::OnExecute()
	{	BlockThread bThread;

		bThread.start();
		bThread.start();

		return false;
	}

	bool TestThread::TestBug2::OnExecute()
	{	KillThread kThread;

		kThread.start();
		kThread.join(3000);
		if (kThread.running())
			return false;
		return true;
	}
};	// !OONet namespace

