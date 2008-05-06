#include "./test_mutex.hpp"
#include <oonet/thread.hpp>
#include <time.h>

namespace oonet
{
	namespace test
	{
		test_mutex test_mutex_inst;

		// A un protected object
		class Obj
		{
		private:
			int total;
		public:
			// Default constructor
			Obj()
			{   total = 0;  }

			virtual ~Obj(){}

			// Add a value
			virtual void add(int val)
			{
				int a;
				a = total;
				mt::thread::sleep(100);
				a += val;
				total = a;
			}

			// Decrease value
			virtual void dec(int val)
			{
				int a;
				a = total;
				mt::thread::sleep(100);
				a -= val;
				total = a;
			}

			int getVal()
			{   return total;   }

			void reset()
			{   total = 0;  }

		} nonSafe;

		// A protected object
		class SafeObj : public Obj , protected mt::mutex
		{
		public:
			virtual void add(int val)
			{
				lock();
				Obj::add(val);
				unlock();
			}

			virtual void dec(int val)
			{
				lock();
				Obj::dec(val);
				unlock();
			}
		}   Safe;

		// A thread playing with unprotected
		class NonSafeThread : public mt::thread
		{
		public:
			~NonSafeThread()
			{
				join();
			}

			virtual void operator()()
			{
				nonSafe.add(10);
			}
		} nonSafeThreads[100];


		// A thread playing with protected objects
		class SafeThread : public mt::thread
		{
		public:
			~SafeThread()
			{
				join();
			}

			virtual void operator()()
			{
				Safe.add(10);
			}
		} SafeThreads[100];


		// Dead lock detector
		class TestDoubleLockThread : public mt::thread
		{
		protected:
			mt::mutex mut;

			virtual void operator()()
			{
				// Try to lock twice from same thread
				mut.lock();
				mut.lock();
			}
		};

		class LockAMutexAndWait : public mt::thread
		{
		public:
			mt::mutex * pMutex;
			long waitfor_ms;
			virtual void operator()()
			{
				// Try to lock twice from same thread
				pMutex->lock();
				mt::thread::sleep(waitfor_ms);
			}

			~LockAMutexAndWait()
			{   join(mt::Infinity); }
		};

		bool test_mutex::TestNonSafe::operator()()
		{   nonSafe.reset();

			// Start threads
			for(int i = 0;i < 100; i++)
				nonSafeThreads[i].start();

			// Wait to finish
			for(int i = 0;i < 100;i++)
				nonSafeThreads[i].join(mt::Infinity);

			if (nonSafe.getVal() == 1000)
				return false;
			return true;
		}

		bool test_mutex::TestSafeData::operator()()
		{   Safe.reset();

			for(int i = 0;i < 100;i++)
				SafeThreads[i].start();

			// Wait to finish
			for(int i = 0;i < 100;i++)
				SafeThreads[i].join(mt::Infinity);

			// Check results
			if (Safe.getVal() != 1000)
				return false;

			return true;
		}

		bool test_mutex::TestRecursiveMutex::operator()()
		{	TestDoubleLockThread dLockThread;

			// start the double lock thread
			dLockThread.start();

			// Wait for a normal period to lock
			dLockThread.join(3000);

			return true;
		}

		bool test_mutex::TestLockTimeOut::operator()()
		{	mt::mutex mymut;
			LockAMutexAndWait LockThread;

			LockThread.pMutex = &mymut;
			LockThread.waitfor_ms = 8000;
			LockThread.start();
			mt::thread::sleep(1000);

			// Try to lock
			mymut.lock(1500);
			double tm_passed = time_passed();
			if ((tm_passed > 2700) || ( tm_passed < 2300))
				return false;
			return true;
		}
	};	// !test namespace
};	// !oonet namespace
