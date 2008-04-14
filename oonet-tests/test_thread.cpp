#include "test_thread.hpp"
#include <oonet/thread.hpp>
#include <time.h>

namespace oonet
{
	static TestThread theTestThread;

	// Global variables for thread
	bool ThreadRunned;
	int threadCount;

	// Throw a thread
	class SimpleThread : public mt::thread
	{
	public:
		~SimpleThread()
		{
		    join(mt::Infinity);
            threadCount --;
		}
		protected:
			// Implement run
			virtual void operator()()
			{
				ThreadRunned = true;
				threadCount ++;
			}

	};

	// A thread for blocking infinitly
	class BlockThread : public mt::thread
	{
    protected:
        bool bPlay, bUsed;
		mt::semaphore sema;
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
            join(mt::Infinity);
		}
		protected:
			// Implement run
			virtual void operator()()
			{
			    bPlay = true;
				ThreadRunned = true;
				sema.post();
				while(bPlay)
					sleep(100);
			}

	};

	// A thread for blocking infinitly
	class KillThread : public mt::thread
	{
	public:
		~KillThread()
		{
			threadCount --;
		}
		protected:
			// Implement run
			virtual void operator()()
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
		mt::thread::sleep(1000);	// Wait for 3 seconds

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

			myThread[i]->join(mt::Infinity);
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
		mt::thread::sleep(testtime * 1000);
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
		bThread.join(mt::Infinity);
        if (bThread.running())
			return false;
		bThread.join(mt::Infinity);
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

};	// !oonet namespace

