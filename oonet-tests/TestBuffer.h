#ifndef BUFFER_TEST_H_INCLUDED
#define BUFFER_TEST_H_INCLUDED

#include "Test.h"

namespace OONet
{
	class TestBuffer
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestCtor, _T("Ctor() "));
		OONET_DECLARESUBTEST(TestSize, _T("Size() quality "));
		OONET_DECLARESUBTEST(TestSizeSpeed, _T("Size() speed 1Mtimes"));
		OONET_DECLARESUBTEST(TestFlush, _T("Flush()"));
		OONET_DECLARESUBTEST(TestFlushSpeed, _T("Flush() speed 100Ktimes"));
		OONET_DECLARESUBTEST(TestByteOrder, _T("Push,Pop order check"));
		OONET_DECLARESUBTEST(TestPeekPopCompability, _T("Peek&Pop must be same"));
		OONET_DECLARESUBTEST(TestPushFrontSpeed, _T("PushFront() speed 1k"));
		OONET_DECLARESUBTEST(TestPopFrontSpeed, _T("PopFront() speed 100k"));
		OONET_DECLARESUBTEST(TestPeekFrontSpeed, _T("PeekFront() speed 100k"));
		OONET_DECLARESUBTEST(TestPushBackSpeed, _T("PushFront() speed 1k"));
		OONET_DECLARESUBTEST(TestPopBackSpeed, _T("PopFront() speed 100k"));
		OONET_DECLARESUBTEST(TestPeekBackSpeed, _T("PeekFront() speed 100k"));

	public:
		// Constructor
		TestBuffer()
			:Test(_T("Buffer"))
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
		}

	} ;	// !TestBuffer
};	// !OONet namespace

#endif // BUFFER_TEST_H_INCLUDED
