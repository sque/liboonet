#ifndef BUFFER_TEST_H_INCLUDED
#define BUFFER_TEST_H_INCLUDED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_buffer
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARE_SUBTEST(TestCtor, "Ctor() ");
			OONET_DECLARE_SUBTEST(TestSize, "Size() quality ");
			OONET_DECLARE_SUBTEST_SPEED(TestSizeSpeed, "Size() speed 1Mtimes");
			OONET_DECLARE_SUBTEST(TestFlush, "Flush()");
			OONET_DECLARE_SUBTEST_SPEED(TestFlushSpeed, "Flush() speed 100Ktimes");
			OONET_DECLARE_SUBTEST(TestByteOrder, "Push,Pop order check");
			OONET_DECLARE_SUBTEST(TestPeekPopCompability, "Peek&Pop must be same");
			OONET_DECLARE_SUBTEST_SPEED(TestPushFrontSpeed, "PushFront() speed 1k");
			OONET_DECLARE_SUBTEST_SPEED(TestPopFrontSpeed, "PopFront() speed 100k");
			OONET_DECLARE_SUBTEST_SPEED(TestPeekFrontSpeed, "PeekFront() speed 100k");
			OONET_DECLARE_SUBTEST_SPEED(TestPushBackSpeed, "PushFront() speed 1k");
			OONET_DECLARE_SUBTEST_SPEED(TestPopBackSpeed, "PopFront() speed 100k");
			OONET_DECLARE_SUBTEST_SPEED(TestPeekBackSpeed, "PeekFront() speed 100k");

		public:
			// Constructor
			test_buffer()
				:test_set("buffer")
			{
				OONET_EXECUTE_SUBTEST(TestCtor);
				OONET_EXECUTE_SUBTEST(TestSize);
				OONET_EXECUTE_SUBTEST(TestSizeSpeed);
				OONET_EXECUTE_SUBTEST(TestFlush);
				OONET_EXECUTE_SUBTEST(TestFlushSpeed);
				OONET_EXECUTE_SUBTEST(TestByteOrder);
				OONET_EXECUTE_SUBTEST(TestPeekPopCompability);
				OONET_EXECUTE_SUBTEST(TestPushFrontSpeed);
				OONET_EXECUTE_SUBTEST(TestPopFrontSpeed);
				OONET_EXECUTE_SUBTEST(TestPeekFrontSpeed);
				OONET_EXECUTE_SUBTEST(TestPushBackSpeed);
				OONET_EXECUTE_SUBTEST(TestPopBackSpeed);
				OONET_EXECUTE_SUBTEST(TestPeekBackSpeed);

				register_test(this);
			}

		} ;	// !test_buffer claas
	}	// !test namespace
};	// !oonet namespace

#endif // BUFFER_TEST_H_INCLUDED
