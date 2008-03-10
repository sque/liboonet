#ifndef MUTEX_TEST_H_DEFINED
#define MUTEX_TEST_H_DEFINED

#include "BinaryData.h"
#include "Test.h"

namespace Slib
{
	class TestSemaphore
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTESTEXC(TestLockTimeOut, _T("Wait() time out 3s"), _T("ExceptionTimeOut"));
		SLIB_DECLARESUBTEST(TestPostWait,  _T("Post() and Wait()") );
		SLIB_DECLARESUBTEST(TestInitialState,  _T("Test initial state") );
		SLIB_DECLARESUBTEST(TestDestructorSignaled,  _T("Destroy when signaled") );
	public:
		// Constructor
		TestSemaphore()
			:Test(_T("Semaphore"))
		{
			SLIB_REGISTERSUBTEST(TestLockTimeOut);
			SLIB_REGISTERSUBTEST(TestPostWait);
			SLIB_REGISTERSUBTEST(TestInitialState);
			SLIB_REGISTERSUBTEST(TestDestructorSignaled);
		}

	} ;	//! TestSemaphore test
};	//! Slib namespace

#endif // MUTEX_TEST_H_DEFINED
