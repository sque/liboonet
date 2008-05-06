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
			OONET_DECLARESUBTEST(TestRecursiveMutex, "Assure Recursive mutex");
			OONET_DECLARESUBTESTEXC(TestLockTimeOut, "Lock() time out 3s", "ExceptionTimeOut");
			OONET_DECLARESUBTEST(TestNonSafe, "1000 Thread unsafe data");
			OONET_DECLARESUBTEST(TestSafeData, "1000 Thread safe data");

		public:
			// Constructor
			test_mutex()
				:test_set("mt::mutex")
			{
				OONET_REGISTERSUBTEST(TestRecursiveMutex);
				OONET_REGISTERSUBTEST(TestLockTimeOut);
				OONET_REGISTERSUBTEST(TestNonSafe);
				OONET_REGISTERSUBTEST(TestSafeData);

				register_test(this);
			}

		} ;	// !test_mutex class
	};	// !test namespace
};	// !oonet namespace

#endif // MUTEX_TEST_H_DEFINED
