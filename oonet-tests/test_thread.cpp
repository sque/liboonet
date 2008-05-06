#include "test_thread.hpp"
#include <oonet/thread.hpp>
#include <time.h>

namespace oonet
{
	namespace test
	{
		static test_thread test_thread_inst;

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
		bool test_thread::TestCtor::operator()()
		{	SimpleThread myThread;

			ThreadRunned = false;

			myThread.start();
			mt::thread::sleep(1000);	// Wait for 3 seconds

			return ThreadRunned;
		}

		// Sub tests implementation
		bool test_thread::TestSpam100::operator()()
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


		bool test_thread::TestSleepAccuracy::operator()()
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

		bool test_thread::TestJoinTimeout::operator()()
		{
			BlockThread bThread;
			bThread.start();
			bThread.join(3000);

			return false;
		}

		bool test_thread::TestJoinQuality::operator()()
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

		bool test_thread::TestBug1::operator()()
		{
			SimpleThread * pThread = new SimpleThread;
			delete pThread;
			return true;
		}


		bool test_thread::TestFastSpam100::operator()()
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

		bool test_thread::TestDoubleStart::operator()()
		{	BlockThread bThread;

			bThread.start();
			bThread.start();

			return false;
		}
	}	// !test namespace
};	// !oonet namespace

