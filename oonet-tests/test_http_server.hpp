#ifndef HTTPSERVER_TEST_H_DEFINED
#define HTTPSERVER_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_http_server
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
			OONET_DECLARE_SUBTEST(TestDCInvalidClients, "DC invalid clients");
			OONET_DECLARE_SUBTEST(TestPureVirtuals1, "Pure Virtual Calls");
			OONET_DECLARE_SUBTEST(TestDoS1, "Emulate DoS#1");
		public:
			// Constructor
			test_http_server()
				:test_set("http::server")
			{
				OONET_EXECUTE_SUBTEST(TestCtor);
				OONET_EXECUTE_SUBTEST(TestStart);
				OONET_EXECUTE_SUBTEST(TestDoubleStart);
				OONET_EXECUTE_SUBTEST(TestStartRecovery);
				OONET_EXECUTE_SUBTEST(TestStop);
				OONET_EXECUTE_SUBTEST(TestStopWrong1);
				OONET_EXECUTE_SUBTEST(TestStopWrong2);
				OONET_EXECUTE_SUBTEST(TestStopCleanup);
				OONET_EXECUTE_SUBTEST(TestDCInvalidClients);
				OONET_EXECUTE_SUBTEST(TestPureVirtuals1);
				OONET_EXECUTE_SUBTEST(TestDoS1);

				register_test(this);
			}

		} ;	// !test_http_server class
	}	// !test namespace
};	// !oonet namespace

#endif // HTTPSERVER_TEST_H_DEFINED
