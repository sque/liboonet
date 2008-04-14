#ifndef THREAD_TEST_H_DEFINED
#define THREAD_TEST_H_DEFINED

#include "Test.h"

namespace oonet
{
	class TestThread
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestCtor,  _T("Thread() simple") );
		OONET_DECLARESUBTEST(TestSleepAccuracy,  _T("Sleep() accuracy 5sec") );
		OONET_DECLARESUBTESTEXC(TestJoinTimeout,  _T("Join() time out 3sec"), _T("ExceptionTimeOut") );
		OONET_DECLARESUBTEST(TestJoinQuality,  _T("Join() quality"));
		OONET_DECLARESUBTEST(TestSpam100,  _T("Spam 100 threads") );
		OONET_DECLARESUBTEST(TestFastSpam100,  _T("Fast: new,start,del") );
		OONET_DECLARESUBTESTEXC(TestDoubleStart,  _T("Start() twice"), _T("ExceptionThreadAlreadyStarted") );
		OONET_DECLARESUBTEST(TestBug1, _T("B#1: create and destroy") );

	public:
		// Constructor
		TestThread()
			:Test(_T("mt::thread"))
		{

			OONET_REGISTERSUBTEST(TestCtor);
			OONET_REGISTERSUBTEST(TestSleepAccuracy);
			OONET_REGISTERSUBTEST(TestJoinTimeout);
			OONET_REGISTERSUBTEST(TestJoinQuality);
			OONET_REGISTERSUBTEST(TestSpam100);
			OONET_REGISTERSUBTEST(TestFastSpam100);
			OONET_REGISTERSUBTEST(TestDoubleStart);
			OONET_REGISTERSUBTEST(TestBug1);
		}

	} ;	// !TestThread class
};	// !oonet namespace

#endif // THREAD_TEST_H_DEFINED
