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
			OONET_DECLARESUBTESTEXC(TestLockTimeOut, "Wait() time out 3s", "ExceptionTimeOut");
			OONET_DECLARESUBTEST(TestPostWait, "Post() and Wait()");
			OONET_DECLARESUBTEST(TestInitialState, "Test initial state");
			OONET_DECLARESUBTEST(TestDestructorSignaled, "Destroy when signaled");
		public:
			// Constructor
			test_semaphore()
				:test_set("mt::semaphore")
			{
				OONET_REGISTERSUBTEST(TestLockTimeOut);
				OONET_REGISTERSUBTEST(TestPostWait);
				OONET_REGISTERSUBTEST(TestInitialState);
				OONET_REGISTERSUBTEST(TestDestructorSignaled);

				register_test(this);
			}

		} ;	// !test_semaphore test
	}	// !test namespace
};	// !oonet namespace

#endif // MUTEX_TEST_H_DEFINED
