#include "test_semaphore.hpp"
#include "semaphore.hpp"
#include "thread.hpp"

namespace oonet
{
	TestSemaphore theTestSemaphore;

	class TestThreadSemaphore : mt::thread
	{

	};

	bool TestSemaphore::TestLockTimeOut::OnExecute()
	{	mt::semaphore mySema;

		mySema.wait(3000);
		return false;
	}

	bool TestSemaphore::TestInitialState::OnExecute()
	{	mt::semaphore mySema(3);

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
	{	mt::semaphore mySema;

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
	{	mt::semaphore mySema;

		mySema.post();	// Signale it and wait to destruct on exit of function
		return true;
	}
};	// !oonet namespace
