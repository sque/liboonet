#include "TestSemaphore.h"
#include "Semaphore.h"
#include "Thread.h"

namespace Slib
{
	TestSemaphore theTestSemaphore;

	class TestThreadSemaphore : MT::Thread
	{

	};

	bool TestSemaphore::TestLockTimeOut::OnExecute()
	{	MT::Semaphore mySema;

		mySema.wait(3000);
		return false;
	}

	bool TestSemaphore::TestInitialState::OnExecute()
	{	MT::Semaphore mySema(3);

		// We can wait 3 times
		mySema.wait(3000);
		mySema.wait(3000);
		mySema.wait(3000);

		// 4th must timeout!
		try	{	mySema.wait(3000);	}
		catch(ExceptionTimeOut & e)
		{	e = e; return true;	}

		return false;
	}

	bool TestSemaphore::TestPostWait::OnExecute()
	{	MT::Semaphore mySema;

		// Post 5 times
		mySema.post();
		mySema.post();
		mySema.post();
		mySema.post();
		mySema.post();

		// Wait 5 times
		mySema.wait();
		mySema.wait();
		mySema.wait();
		mySema.wait();
		mySema.wait();

		// 6th must timeout!
		try	{	mySema.wait(3000);	}
		catch(ExceptionTimeOut & e)
		{	e = e; return true;	}

		return false;
	}

	bool TestSemaphore::TestDestructorSignaled::OnExecute()
	{	MT::Semaphore mySema;

		mySema.post();	// Signale it and wait to destruct on exit of function
		return true;
	}
};
