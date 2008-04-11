#ifndef INETSERVER_TEST_H_DEFINED
#define INETSERVER_TEST_H_DEFINED

#include "Test.h"

namespace oonet
{
	class test_netserver
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
		/*OONET_DECLARESUBTEST(TestFree, _T("Free() quality"));
		OONET_DECLARESUBTESTEXC(TestFreeWrong1, _T("Free() wrong"), _T("ExceptionResourceBusy"));
		OONET_DECLARESUBTESTEXC(TestFreeWrong2, _T("Free() wrong"), _T("ExceptionAccessDenied"));
		OONET_DECLARESUBTEST(TestFreeDisconnected, _T("FreeDisconnected()"));*/
	public:
		// Constructor
		test_netserver()
			:Test(_T("netserver"))
		{
			OONET_REGISTERSUBTEST(TestCtor);
			OONET_REGISTERSUBTEST(TestStart);
			OONET_REGISTERSUBTEST(TestDoubleStart);
			OONET_REGISTERSUBTEST(TestStartRecovery);
			OONET_REGISTERSUBTEST(TestStop);
			OONET_REGISTERSUBTEST(TestStopWrong1);
			OONET_REGISTERSUBTEST(TestStopWrong2);
			OONET_REGISTERSUBTEST(TestStopCleanup);
			/*OONET_REGISTERSUBTEST(TestFree);
			OONET_REGISTERSUBTEST(TestFreeWrong1);
			OONET_REGISTERSUBTEST(TestFreeWrong2);
			OONET_REGISTERSUBTEST(TestFreeDisconnected);*/
		}

	} ;	// !TestInetServer class
};	// !oonet namespace

#endif // INETCLIENT_TEST_H_DEFINED
