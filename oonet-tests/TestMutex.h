#ifndef MUTEX_TEST_H_DEFINED
#define MUTEX_TEST_H_DEFINED

#include "binary_data.hpp"
#include "Test.h"

namespace oonet
{
	class TestMutex
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestRecursiveMutex, _T("Assure Recursive mutex"));
		OONET_DECLARESUBTESTEXC(TestLockTimeOut, _T("Lock() time out 3s"), _T("ExceptionTimeOut"));
		OONET_DECLARESUBTEST(TestNonSafe,  _T("1000 Thread unsafe data") );
		OONET_DECLARESUBTEST(TestSafeData,  _T("1000 Thread safe data") );

	public:
		// Constructor
		TestMutex()
			:Test(_T("mt::mutex"))
		{
			OONET_REGISTERSUBTEST(TestRecursiveMutex);
			OONET_REGISTERSUBTEST(TestLockTimeOut);
			OONET_REGISTERSUBTEST(TestNonSafe);
			OONET_REGISTERSUBTEST(TestSafeData);
		}

	} ;	// !TestMutex class
};	// !oonet namespace

#endif // MUTEX_TEST_H_DEFINED
