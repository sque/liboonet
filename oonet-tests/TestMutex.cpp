#include "TestMutex.h"
#include "Thread.h"
#include <time.h>

namespace Slib
{
	static TestMutex theTestMutex;

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
			MT::Thread::sleep(100);
			a += val;
			total = a;
		}

		// Decrease value
		virtual void dec(int val)
		{
			int a;
			a = total;
			MT::Thread::sleep(100);
			a -= val;
			total = a;
		}

		int getVal()
		{   return total;   }

		void reset()
		{   total = 0;  }

	} nonSafe;

	// A protected object
	class SafeObj : public Obj , protected MT::Mutex
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
	class NonSafeThread : public MT::Thread
	{
	public:
		~NonSafeThread()
		{
			join();
		}

		virtual void ThreadRoutine(void)
		{
			nonSafe.add(10);
		}
	} nonSafeThreads[100];


	// A thread playing with protected objects
	class SafeThread : public MT::Thread
	{
	public:
		~SafeThread()
		{
			join();
		}

		virtual void ThreadRoutine(void)
		{
			Safe.add(10);
		}
	} SafeThreads[100];


	// Dead lock detector
	class TestDoubleLockThread : public MT::Thread
	{
	protected:
		MT::Mutex mut;

		virtual void ThreadRoutine(void)
		{
			// Try to lock twice from same thread
			mut.lock();
			mut.lock();
		}
	};

	class LockAMutexAndWait : public MT::Thread
	{
	public:
		MT::Mutex * pMutex;
		long waitfor_ms;
		virtual void ThreadRoutine(void)
		{
			// Try to lock twice from same thread
			pMutex->lock();
			MT::Thread::sleep(waitfor_ms);
		}

		~LockAMutexAndWait()
		{   join(MT::Infinity); }
	};

	bool TestMutex::TestNonSafe::OnExecute()
	{   nonSafe.reset();

		// Start threads
		for(int i = 0;i < 100; i++)
			nonSafeThreads[i].start();

		// Wait to finish
		for(int i = 0;i < 100;i++)
			nonSafeThreads[i].join(MT::Infinity);

		if (nonSafe.getVal() == 1000)
			return false;
		return true;
	}

	bool TestMutex::TestSafeData::OnExecute()
	{   Safe.reset();

		for(int i = 0;i < 100;i++)
			SafeThreads[i].start();

		// Wait to finish
		for(int i = 0;i < 100;i++)
			SafeThreads[i].join(MT::Infinity);

		// Check results
		if (Safe.getVal() != 1000)
			return false;

		return true;
	}

	bool TestMutex::TestRecursiveMutex::OnExecute()
	{	TestDoubleLockThread dLockThread;

		// start the double lock thread
		dLockThread.start();

		// Wait for a normal period to lock
		dLockThread.join(3000);

		return true;
	}

	bool TestMutex::TestLockTimeOut::OnExecute()
	{	MT::Mutex mymut;
		LockAMutexAndWait LockThread;

		LockThread.pMutex = &mymut;
		LockThread.waitfor_ms = 8000;
		LockThread.start();
		MT::Thread::sleep(2000);

		// Try to lock
		mymut.lock(1500);
		return true;
	}
};	//! Slib namespace