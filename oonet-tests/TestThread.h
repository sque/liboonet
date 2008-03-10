#ifndef THREAD_TEST_H_DEFINED
#define THREAD_TEST_H_DEFINED

#include "BinaryData.h"
#include "Test.h"

namespace OONet
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
		OONET_DECLARESUBTEST(TestKill,  _T("Kill() Kill a blocking") );
		OONET_DECLARESUBTEST(TestSpam100,  _T("Spam 100 threads") );
		OONET_DECLARESUBTEST(TestFastSpam100,  _T("Fast: new,start,del") );
		OONET_DECLARESUBTESTEXC(TestDoubleStart,  _T("Start() twice"), _T("ExceptionThreadAlreadyStarted") );
		OONET_DECLARESUBTEST(TestBug1, _T("B#1: create and destroy") );
		OONET_DECLARESUBTEST(TestBug2, _T("B#2: Kill() inside thread"));

	public:
		// Constructor
		TestThread()
			:Test(_T("Thread"))
		{
			OONET_REGISTERSUBTEST(TestSleepAccuracy);
			OONET_REGISTERSUBTEST(TestCtor);
			OONET_REGISTERSUBTEST(TestJoinQuality);
			OONET_REGISTERSUBTEST(TestJoinTimeout);
			// An katargisoume tin kill afto den yparxei OONET_REGISTERSUBTEST(TestKill);
			OONET_REGISTERSUBTEST(TestSpam100);
			OONET_REGISTERSUBTEST(TestFastSpam100);
			OONET_REGISTERSUBTEST(TestDoubleStart);
			OONET_REGISTERSUBTEST(TestBug1);
			// An katargisoume tin kill afto den yparxei OONET_REGISTERSUBTEST(TestBug2);
		}

	} ;	// !TestThread class
};	// !OONet namespace

#endif // THREAD_TEST_H_DEFINED
