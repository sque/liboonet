#ifndef BUFFER_TEST_H_INCLUDED
#define BUFFER_TEST_H_INCLUDED

#include "Test.h"

namespace Slib
{
	class TestBuffer
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTEST(TestCtor, _T("Ctor() "));
		SLIB_DECLARESUBTEST(TestSize, _T("Size() quality "));
		SLIB_DECLARESUBTEST(TestSizeSpeed, _T("Size() speed 1Mtimes"));
		SLIB_DECLARESUBTEST(TestFlush, _T("Flush()"));
		SLIB_DECLARESUBTEST(TestFlushSpeed, _T("Flush() speed 100Ktimes"));
		SLIB_DECLARESUBTEST(TestByteOrder, _T("Push,Pop order check"));
		SLIB_DECLARESUBTEST(TestPeekPopCompability, _T("Peek&Pop must be same"));
		SLIB_DECLARESUBTEST(TestPushFrontSpeed, _T("PushFront() speed 1k"));
		SLIB_DECLARESUBTEST(TestPopFrontSpeed, _T("PopFront() speed 100k"));
		SLIB_DECLARESUBTEST(TestPeekFrontSpeed, _T("PeekFront() speed 100k"));
		SLIB_DECLARESUBTEST(TestPushBackSpeed, _T("PushFront() speed 1k"));
		SLIB_DECLARESUBTEST(TestPopBackSpeed, _T("PopFront() speed 100k"));
		SLIB_DECLARESUBTEST(TestPeekBackSpeed, _T("PeekFront() speed 100k"));

	public:
		// Constructor
		TestBuffer()
			:Test(_T("Buffer"))
		{
			SLIB_REGISTERSUBTEST(TestCtor);
			SLIB_REGISTERSUBTEST(TestSize);
			SLIB_REGISTERSUBTEST(TestSizeSpeed);
			SLIB_REGISTERSUBTEST(TestFlush);
			SLIB_REGISTERSUBTEST(TestFlushSpeed);
			SLIB_REGISTERSUBTEST(TestByteOrder);
			SLIB_REGISTERSUBTEST(TestPeekPopCompability);
			SLIB_REGISTERSUBTEST(TestPushFrontSpeed);
			SLIB_REGISTERSUBTEST(TestPopFrontSpeed);
			SLIB_REGISTERSUBTEST(TestPeekFrontSpeed);
			SLIB_REGISTERSUBTEST(TestPushBackSpeed);
			SLIB_REGISTERSUBTEST(TestPopBackSpeed);
			SLIB_REGISTERSUBTEST(TestPeekBackSpeed);
		}

	} ;	//! BinaryData test
};	//! Slib namespace

#endif // BUFFER_TEST_H_INCLUDED
