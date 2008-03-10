#ifndef MUTEX_TEST_H_DEFINED
#define MUTEX_TEST_H_DEFINED

#include "BinaryData.h"
#include "Test.h"

namespace Slib
{
	class TestMutex
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTEST(TestRecursiveMutex, _T("Assure Recursive mutex"));
		SLIB_DECLARESUBTESTEXC(TestLockTimeOut, _T("Lock() time out 3s"), _T("ExceptionTimeOut"));
		SLIB_DECLARESUBTEST(TestNonSafe,  _T("1000 Thread unsafe data") );
		SLIB_DECLARESUBTEST(TestSafeData,  _T("1000 Thread safe data") );

	public:
		// Constructor
		TestMutex()
			:Test(_T("Mutex"))
		{
			SLIB_REGISTERSUBTEST(TestRecursiveMutex);
			SLIB_REGISTERSUBTEST(TestLockTimeOut);
			SLIB_REGISTERSUBTEST(TestNonSafe);
			SLIB_REGISTERSUBTEST(TestSafeData);
		}

	} ;	//! TestMutex test
};	//! Slib namespace

#endif // MUTEX_TEST_H_DEFINED
