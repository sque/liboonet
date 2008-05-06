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
			OONET_DECLARESUBTEST(TestCtor, "Ctor()");
			OONET_DECLARESUBTEST(TestStart, "Start()");
			OONET_DECLARESUBTESTEXC(TestDoubleStart, "Start() double", "ExceptionAlreadyConnected");
			OONET_DECLARESUBTEST(TestStartRecovery, "Start() recovery");
			OONET_DECLARESUBTEST(TestStop, "Stop() quality test");
			OONET_DECLARESUBTEST(TestStopWrong1, "Start() wrong");
			OONET_DECLARESUBTEST(TestStopWrong2, "Start() wrong");
			OONET_DECLARESUBTEST(TestStopCleanup, "Stop() cleanup");
			OONET_DECLARESUBTEST(TestDCInvalidClients, "DC invalid clients");
			OONET_DECLARESUBTEST(TestPureVirtuals1, "Pure Virtual Calls");
			OONET_DECLARESUBTEST(TestDoS1, "Emulate DoS#1");
		public:
			// Constructor
			test_http_server()
				:test_set("http::server")
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

				register_test(this);
			}

		} ;	// !test_http_server class
	}	// !test namespace
};	// !oonet namespace

#endif // HTTPSERVER_TEST_H_DEFINED
