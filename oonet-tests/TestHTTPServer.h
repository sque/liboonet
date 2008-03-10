#ifndef HTTPSERVER_TEST_H_DEFINED
#define HTTPSERVER_TEST_H_DEFINED

#include "Test.h"

namespace Slib
{
	class TestHTTPServer
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
		SLIB_DECLARESUBTEST(TestDCInvalidClients, _T("DC invalid clients"));
		SLIB_DECLARESUBTEST(TestPureVirtuals1, _T("Pure Virtual Calls"));
		SLIB_DECLARESUBTEST(TestDoS1, _T("Emulate DoS#1"));
	public:
		// Constructor
		TestHTTPServer()
			:Test(_T("HTTP::Server"))
		{
			SLIB_REGISTERSUBTEST(TestCtor);
			SLIB_REGISTERSUBTEST(TestStart);
			SLIB_REGISTERSUBTEST(TestDoubleStart);
			SLIB_REGISTERSUBTEST(TestStartRecovery);
			SLIB_REGISTERSUBTEST(TestStop);
			SLIB_REGISTERSUBTEST(TestStopWrong1);
			SLIB_REGISTERSUBTEST(TestStopWrong2);
			SLIB_REGISTERSUBTEST(TestStopCleanup);
			SLIB_REGISTERSUBTEST(TestDCInvalidClients);
			SLIB_REGISTERSUBTEST(TestPureVirtuals1);
			SLIB_REGISTERSUBTEST(TestDoS1);
		}

	} ;	//! TestHTTPServer class
};	//! Slib namespace

#endif // HTTPSERVER_TEST_H_DEFINED
