#ifndef INETSERVER_TEST_H_DEFINED
#define INETSERVER_TEST_H_DEFINED

#include "Test.h"

namespace Slib
{
	class TestInetServer
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTEST(TestCtor, _T("Ctor()"));
		SLIB_DECLARESUBTEST(TestStart, _T("Start()"));
		SLIB_DECLARESUBTESTEXC(TestDoubleStart, _T("Start() double"), _T("ExceptionAlreadyConnected"));
		SLIB_DECLARESUBTEST(TestStartRecovery, _T("Start() recovery"));
		SLIB_DECLARESUBTEST(TestStop, _T("Stop() quality test"));
		SLIB_DECLARESUBTESTEXC(TestStopWrong1, _T("Start() wrong"), _T("ExceptionNotConnected"));
		SLIB_DECLARESUBTESTEXC(TestStopWrong2, _T("Start() wrong"), _T("ExceptionNotConnected"));
		SLIB_DECLARESUBTEST(TestStopCleanup, _T("Stop() cleanup"));
		SLIB_DECLARESUBTEST(TestFree, _T("Free() quality"));
		SLIB_DECLARESUBTESTEXC(TestFreeWrong1, _T("Free() wrong"), _T("ExceptionResourceBusy"));
		SLIB_DECLARESUBTESTEXC(TestFreeWrong2, _T("Free() wrong"), _T("ExceptionAccessDenied"));
		SLIB_DECLARESUBTEST(TestFreeDisconnected, _T("FreeDisconnected()"));
	public:
		// Constructor
		TestInetServer()
			:Test(_T("InetServer"))
		{
			SLIB_REGISTERSUBTEST(TestCtor);
			SLIB_REGISTERSUBTEST(TestStart);
			SLIB_REGISTERSUBTEST(TestDoubleStart);
			SLIB_REGISTERSUBTEST(TestStartRecovery);
			SLIB_REGISTERSUBTEST(TestStop);
			SLIB_REGISTERSUBTEST(TestStopWrong1);
			SLIB_REGISTERSUBTEST(TestStopWrong2);
			SLIB_REGISTERSUBTEST(TestStopCleanup);
			SLIB_REGISTERSUBTEST(TestFree);
			SLIB_REGISTERSUBTEST(TestFreeWrong1);
			SLIB_REGISTERSUBTEST(TestFreeWrong2);
			SLIB_REGISTERSUBTEST(TestFreeDisconnected);
		}

	} ;	//! TestInetServer test
};	//! Slib namespace

#endif // INETCLIENT_TEST_H_DEFINED
