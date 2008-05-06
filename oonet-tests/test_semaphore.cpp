#include "test_semaphore.hpp"
#include <oonet/semaphore.hpp>
#include <oonet/thread.hpp>

namespace oonet
{
	namespace test
	{
		test_semaphore test_semaphore_inst;

		class TestThreadSemaphore : mt::thread
		{

		};

		bool test_semaphore::TestLockTimeOut::operator()()
		{	mt::semaphore mySema;

			mySema.wait(3000);
			return false;
		}

		bool test_semaphore::TestInitialState::operator()()
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

		bool test_semaphore::TestPostWait::operator()()
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

		bool test_semaphore::TestDestructorSignaled::operator()()
		{	mt::semaphore mySema;

			mySema.post();	// Signale it and wait to destruct on exit of function
			return true;
		}
	};	// !test namespace
};	// !oonet namespace
