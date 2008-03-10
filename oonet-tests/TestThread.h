#ifndef THREAD_TEST_H_DEFINED
#define THREAD_TEST_H_DEFINED

#include "BinaryData.h"
#include "Test.h"

namespace Slib
{
	class TestThread
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTEST(TestCtor,  _T("Thread() simple") );
		SLIB_DECLARESUBTEST(TestSleepAccuracy,  _T("Sleep() accuracy 5sec") );
		SLIB_DECLARESUBTESTEXC(TestJoinTimeout,  _T("Join() time out 3sec"), _T("ExceptionTimeOut") );
		SLIB_DECLARESUBTEST(TestJoinQuality,  _T("Join() quality"));
		SLIB_DECLARESUBTEST(TestKill,  _T("Kill() Kill a blocking") );
		SLIB_DECLARESUBTEST(TestSpam100,  _T("Spam 100 threads") );
		SLIB_DECLARESUBTEST(TestFastSpam100,  _T("Fast: new,start,del") );
		SLIB_DECLARESUBTESTEXC(TestDoubleStart,  _T("Start() twice"), _T("ExceptionThreadAlreadyStarted") );
		SLIB_DECLARESUBTEST(TestBug1, _T("B#1: create and destroy") );
		SLIB_DECLARESUBTEST(TestBug2, _T("B#2: Kill() inside thread"));

	public:
		// Constructor
		TestThread()
			:Test(_T("Thread"))
		{
			SLIB_REGISTERSUBTEST(TestSleepAccuracy);
			SLIB_REGISTERSUBTEST(TestCtor);
			SLIB_REGISTERSUBTEST(TestJoinQuality);
			SLIB_REGISTERSUBTEST(TestJoinTimeout);
			// An katargisoume tin kill afto den yparxei SLIB_REGISTERSUBTEST(TestKill);
			SLIB_REGISTERSUBTEST(TestSpam100);
			SLIB_REGISTERSUBTEST(TestFastSpam100);
			SLIB_REGISTERSUBTEST(TestDoubleStart);
			SLIB_REGISTERSUBTEST(TestBug1);
			// An katargisoume tin kill afto den yparxei SLIB_REGISTERSUBTEST(TestBug2);
		}

	} ;	//! TestThread test
};	//! Slib namespace

#endif // THREAD_TEST_H_DEFINED
