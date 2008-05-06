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
			OONET_DECLARESUBTEST(TestCtor, "Ctor() ");
			OONET_DECLARESUBTEST(TestSize, "Size() quality ");
			OONET_DECLARESUBTEST(TestSizeSpeed, "Size() speed 1Mtimes");
			OONET_DECLARESUBTEST(TestFlush, "Flush()");
			OONET_DECLARESUBTEST(TestFlushSpeed, "Flush() speed 100Ktimes");
			OONET_DECLARESUBTEST(TestByteOrder, "Push,Pop order check");
			OONET_DECLARESUBTEST(TestPeekPopCompability, "Peek&Pop must be same");
			OONET_DECLARESUBTEST(TestPushFrontSpeed, "PushFront() speed 1k");
			OONET_DECLARESUBTEST(TestPopFrontSpeed, "PopFront() speed 100k");
			OONET_DECLARESUBTEST(TestPeekFrontSpeed, "PeekFront() speed 100k");
			OONET_DECLARESUBTEST(TestPushBackSpeed, "PushFront() speed 1k");
			OONET_DECLARESUBTEST(TestPopBackSpeed, "PopFront() speed 100k");
			OONET_DECLARESUBTEST(TestPeekBackSpeed, "PeekFront() speed 100k");

		public:
			// Constructor
			test_buffer()
				:test_set("buffer")
			{
				OONET_REGISTERSUBTEST(TestCtor);
				OONET_REGISTERSUBTEST(TestSize);
				OONET_REGISTERSUBTEST(TestSizeSpeed);
				OONET_REGISTERSUBTEST(TestFlush);
				OONET_REGISTERSUBTEST(TestFlushSpeed);
				OONET_REGISTERSUBTEST(TestByteOrder);
				OONET_REGISTERSUBTEST(TestPeekPopCompability);
				OONET_REGISTERSUBTEST(TestPushFrontSpeed);
				OONET_REGISTERSUBTEST(TestPopFrontSpeed);
				OONET_REGISTERSUBTEST(TestPeekFrontSpeed);
				OONET_REGISTERSUBTEST(TestPushBackSpeed);
				OONET_REGISTERSUBTEST(TestPopBackSpeed);
				OONET_REGISTERSUBTEST(TestPeekBackSpeed);

				register_test(this);
			}

		} ;	// !test_buffer claas
	}	// !test namespace
};	// !oonet namespace

#endif // BUFFER_TEST_H_INCLUDED
