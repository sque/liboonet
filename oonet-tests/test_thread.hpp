#ifndef THREAD_TEST_H_DEFINED
#define THREAD_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_thread
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARESUBTEST(TestCtor, "Thread() simple");
			OONET_DECLARESUBTEST(TestSleepAccuracy, "Sleep() accuracy 5sec");
			OONET_DECLARESUBTESTEXC(TestJoinTimeout, "Join() time out 3sec", "ExceptionTimeOut");
			OONET_DECLARESUBTEST(TestJoinQuality, "Join() quality");
			OONET_DECLARESUBTEST(TestSpam100, "Spam 100 threads");
			OONET_DECLARESUBTEST(TestFastSpam100, "Fast: new,start,del");
			OONET_DECLARESUBTESTEXC(TestDoubleStart, "Start() twice", "ExceptionThreadAlreadyStarted");
			OONET_DECLARESUBTEST(TestBug1, "B#1: create and destroy");

		public:
			// Constructor
			test_thread()
				:test_set("mt::thread")
			{

				OONET_REGISTERSUBTEST(TestCtor);
				OONET_REGISTERSUBTEST(TestSleepAccuracy);
				OONET_REGISTERSUBTEST(TestJoinTimeout);
				OONET_REGISTERSUBTEST(TestJoinQuality);
				OONET_REGISTERSUBTEST(TestSpam100);
				OONET_REGISTERSUBTEST(TestFastSpam100);
				OONET_REGISTERSUBTEST(TestDoubleStart);
				OONET_REGISTERSUBTEST(TestBug1);

				register_test(this);
			}

		} ;	// !test_thread class
	}	// !test namespace
};	// !oonet namespace

#endif // THREAD_TEST_H_DEFINED
