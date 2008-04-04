#ifndef MUTEX_TEST_H_DEFINED
#define MUTEX_TEST_H_DEFINED

#include "binary_data.hpp"
#include "Test.h"

namespace oonet
{
	class TestSemaphore
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTESTEXC(TestLockTimeOut, _T("Wait() time out 3s"), _T("ExceptionTimeOut"));
		OONET_DECLARESUBTEST(TestPostWait,  _T("Post() and Wait()") );
		OONET_DECLARESUBTEST(TestInitialState,  _T("Test initial state") );
		OONET_DECLARESUBTEST(TestDestructorSignaled,  _T("Destroy when signaled") );
	public:
		// Constructor
		TestSemaphore()
			:Test(_T("Semaphore"))
		{
			OONET_REGISTERSUBTEST(TestLockTimeOut);
			OONET_REGISTERSUBTEST(TestPostWait);
			OONET_REGISTERSUBTEST(TestInitialState);
			OONET_REGISTERSUBTEST(TestDestructorSignaled);
		}

	} ;	// !TestSemaphore test
};	// !oonet namespace

#endif // MUTEX_TEST_H_DEFINED
