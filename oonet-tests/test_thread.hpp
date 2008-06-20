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
			OONET_DECLARE_SUBTEST(TestCtor, "Thread() simple");
			OONET_DECLARE_SUBTEST(TestSleepAccuracy, "Sleep() accuracy 5sec");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestJoinTimeout, "Join() time out 3sec", "ExceptionTimeOut");
			OONET_DECLARE_SUBTEST(TestJoinQuality, "Join() quality");
			OONET_DECLARE_SUBTEST(TestSpam100, "Spam 100 threads");
			OONET_DECLARE_SUBTEST(TestFastSpam100, "Fast: new,start,del");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestDoubleStart, "Start() twice", "ExceptionThreadAlreadyStarted");
			OONET_DECLARE_SUBTEST(TestBug1, "B#1: create and destroy");

		public:
			// Constructor
			test_thread()
				:test_set("mt::thread")
			{

				OONET_EXECUTE_SUBTEST(TestCtor);
				OONET_EXECUTE_SUBTEST(TestSleepAccuracy);
				OONET_EXECUTE_SUBTEST(TestJoinTimeout);
				OONET_EXECUTE_SUBTEST(TestJoinQuality);
				OONET_EXECUTE_SUBTEST(TestSpam100);
				OONET_EXECUTE_SUBTEST(TestFastSpam100);
				OONET_EXECUTE_SUBTEST(TestDoubleStart);
				OONET_EXECUTE_SUBTEST(TestBug1);

				register_test(this);
			}

		} ;	// !test_thread class
	}	// !test namespace
};	// !oonet namespace

#endif // THREAD_TEST_H_DEFINED
