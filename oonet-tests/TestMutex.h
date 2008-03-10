#ifndef MUTEX_TEST_H_DEFINED
#define MUTEX_TEST_H_DEFINED

#include "BinaryData.h"
#include "Test.h"

namespace OONet
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
			:Test(_T("Mutex"))
		{
			OONET_REGISTERSUBTEST(TestRecursiveMutex);
			OONET_REGISTERSUBTEST(TestLockTimeOut);
			OONET_REGISTERSUBTEST(TestNonSafe);
			OONET_REGISTERSUBTEST(TestSafeData);
		}

	} ;	// !TestMutex class
};	// !OONet namespace

#endif // MUTEX_TEST_H_DEFINED
