#ifndef MUTEX_TEST_H_DEFINED
#define MUTEX_TEST_H_DEFINED

#include "./oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_mutex
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARE_SUBTEST(TestRecursiveMutex, "Assure Recursive mutex");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestLockTimeOut, "Lock() time out 3s", "ExceptionTimeOut");
			OONET_DECLARE_SUBTEST(TestNonSafe, "1000 Thread unsafe data");
			OONET_DECLARE_SUBTEST(TestSafeData, "1000 Thread safe data");

		public:
			// Constructor
			test_mutex()
				:test_set("mt::mutex")
			{
				OONET_EXECUTE_SUBTEST(TestRecursiveMutex);
				OONET_EXECUTE_SUBTEST(TestLockTimeOut);
				OONET_EXECUTE_SUBTEST(TestNonSafe);
				OONET_EXECUTE_SUBTEST(TestSafeData);

				register_test(this);
			}

		} ;	// !test_mutex class
	};	// !test namespace
};	// !oonet namespace

#endif // MUTEX_TEST_H_DEFINED
