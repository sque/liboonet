#ifndef INETSERVER_TEST_H_DEFINED
#define INETSERVER_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_netserver
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARESUBTEST(TestCtor, "Ctor()");
			OONET_DECLARESUBTEST(TestStart, "Start()");
			OONET_DECLARESUBTESTEXC(TestDoubleStart, "Start() double", "ExceptionAlreadyConnected");
			OONET_DECLARESUBTEST(TestStartRecovery, "Start() recovery");
			OONET_DECLARESUBTEST(TestStop, "Stop() quality test");
			OONET_DECLARESUBTEST(TestStopWrong1, "Start() wrong");
			OONET_DECLARESUBTEST(TestStopWrong2, "Start() wrong");
			OONET_DECLARESUBTEST(TestStopCleanup, "Stop() cleanup");
			/*OONET_DECLARESUBTEST(TestFree, _T("Free() quality"));
			OONET_DECLARESUBTESTEXC(TestFreeWrong1, _T("Free() wrong"), _T("ExceptionResourceBusy"));
			OONET_DECLARESUBTESTEXC(TestFreeWrong2, _T("Free() wrong"), _T("ExceptionAccessDenied"));
			OONET_DECLARESUBTEST(TestFreeDisconnected, _T("FreeDisconnected()"));*/
		public:
			// Constructor
			test_netserver()
				:test_set("netserver")
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

				register_test(this);
			}

		} ;	// !test_netserver class
	}	// !test namespace
};	// !oonet namespace

#endif // INETCLIENT_TEST_H_DEFINED
