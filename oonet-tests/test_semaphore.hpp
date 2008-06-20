#ifndef MUTEX_TEST_H_DEFINED
#define MUTEX_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_semaphore
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestLockTimeOut, "Wait() time out 3s", "ExceptionTimeOut");
			OONET_DECLARE_SUBTEST(TestPostWait, "Post() and Wait()");
			OONET_DECLARE_SUBTEST(TestInitialState, "Test initial state");
			OONET_DECLARE_SUBTEST(TestDestructorSignaled, "Destroy when signaled");
		public:
			// Constructor
			test_semaphore()
				:test_set("mt::semaphore")
			{
				OONET_EXECUTE_SUBTEST(TestLockTimeOut);
				OONET_EXECUTE_SUBTEST(TestPostWait);
				OONET_EXECUTE_SUBTEST(TestInitialState);
				OONET_EXECUTE_SUBTEST(TestDestructorSignaled);

				register_test(this);
			}

		} ;	// !test_semaphore test
	}	// !test namespace
};	// !oonet namespace

#endif // MUTEX_TEST_H_DEFINED
