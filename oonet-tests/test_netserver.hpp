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
			OONET_DECLARE_SUBTEST(TestCtor, "Ctor()");
			OONET_DECLARE_SUBTEST(TestStart, "Start()");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestDoubleStart, "Start() double", "ExceptionAlreadyConnected");
			OONET_DECLARE_SUBTEST(TestStartRecovery, "Start() recovery");
			OONET_DECLARE_SUBTEST(TestStop, "Stop() quality test");
			OONET_DECLARE_SUBTEST(TestStopWrong1, "Start() wrong");
			OONET_DECLARE_SUBTEST(TestStopWrong2, "Start() wrong");
			OONET_DECLARE_SUBTEST(TestStopCleanup, "Stop() cleanup");
			/*OONET_DECLARE_SUBTEST(TestFree, _T("Free() quality"));
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestFreeWrong1, _T("Free() wrong"), _T("ExceptionResourceBusy"));
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestFreeWrong2, _T("Free() wrong"), _T("ExceptionAccessDenied"));
			OONET_DECLARE_SUBTEST(TestFreeDisconnected, _T("FreeDisconnected()"));*/
		public:
			// Constructor
			test_netserver()
				:test_set("netserver")
			{
				OONET_EXECUTE_SUBTEST(TestCtor);
				OONET_EXECUTE_SUBTEST(TestStart);
				OONET_EXECUTE_SUBTEST(TestDoubleStart);
				OONET_EXECUTE_SUBTEST(TestStartRecovery);
				OONET_EXECUTE_SUBTEST(TestStop);
				OONET_EXECUTE_SUBTEST(TestStopWrong1);
				OONET_EXECUTE_SUBTEST(TestStopWrong2);
				OONET_EXECUTE_SUBTEST(TestStopCleanup);
				/*OONET_EXECUTE_SUBTEST(TestFree);
				OONET_EXECUTE_SUBTEST(TestFreeWrong1);
				OONET_EXECUTE_SUBTEST(TestFreeWrong2);
				OONET_EXECUTE_SUBTEST(TestFreeDisconnected);*/

				register_test(this);
			}

		} ;	// !test_netserver class
	}	// !test namespace
};	// !oonet namespace

#endif // INETCLIENT_TEST_H_DEFINED
