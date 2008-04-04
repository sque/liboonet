#ifndef HTTPSERVER_TEST_H_DEFINED
#define HTTPSERVER_TEST_H_DEFINED

#include "Test.h"

namespace oonet
{
	class TestHTTPServer
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestCtor, _T("Ctor()"));
		OONET_DECLARESUBTEST(TestStart, _T("Start()"));
		OONET_DECLARESUBTESTEXC(TestDoubleStart, _T("Start() double"), _T("ExceptionAlreadyConnected"));
		OONET_DECLARESUBTEST(TestStartRecovery, _T("Start() recovery"));
		OONET_DECLARESUBTEST(TestStop, _T("Stop() quality test"));
		OONET_DECLARESUBTEST(TestStopWrong1, _T("Start() wrong"));
		OONET_DECLARESUBTEST(TestStopWrong2, _T("Start() wrong"));
		OONET_DECLARESUBTEST(TestStopCleanup, _T("Stop() cleanup"));
		OONET_DECLARESUBTEST(TestDCInvalidClients, _T("DC invalid clients"));
		OONET_DECLARESUBTEST(TestPureVirtuals1, _T("Pure Virtual Calls"));
		OONET_DECLARESUBTEST(TestDoS1, _T("Emulate DoS#1"));
	public:
		// Constructor
		TestHTTPServer()
			:Test(_T("HTTP::Server"))
		{
			OONET_REGISTERSUBTEST(TestCtor);
			OONET_REGISTERSUBTEST(TestStart);
			OONET_REGISTERSUBTEST(TestDoubleStart);
			OONET_REGISTERSUBTEST(TestStartRecovery);
			OONET_REGISTERSUBTEST(TestStop);
			OONET_REGISTERSUBTEST(TestStopWrong1);
			OONET_REGISTERSUBTEST(TestStopWrong2);
			OONET_REGISTERSUBTEST(TestStopCleanup);
			OONET_REGISTERSUBTEST(TestDCInvalidClients);
			OONET_REGISTERSUBTEST(TestPureVirtuals1);
			OONET_REGISTERSUBTEST(TestDoS1);
		}

	} ;	// !TestHTTPServer class
};	// !oonet namespace

#endif // HTTPSERVER_TEST_H_DEFINED
