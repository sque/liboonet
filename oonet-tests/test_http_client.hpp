#ifndef HTTPCLIENT_TEST_H_DEFINED
#define HTTPCLIENT_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_http_client
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARE_SUBTEST(TestCtor, "ctor() default");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestCtorWrong, "ctor() on imposible svr", "ExceptionConnectionRefused");
			OONET_DECLARE_SUBTEST(TestConnect, "connect() on not con");
			OONET_DECLARE_SUBTEST(TestConnectConnected, "connect() on connected");
			OONET_DECLARE_SUBTEST(TestSend, "send() quality");
			OONET_DECLARE_SUBTEST_SPEED(TestSendSpeed, "send() speed 50MB/1k block");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestSendTimeOut, "send() time out", "ExceptionTimeOut");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestSendWrongResponse, "send() wrong response", "ExceptionWrongFormat");
			OONET_DECLARE_SUBTEST(TestReuseDisconnected, "Reuse disconencted");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestSendServerReset, "send() server resets", "ExceptionIncomplete");
		public:
			// Constructor
			test_http_client()
				:test_set("http::client")
			{
				OONET_EXECUTE_SUBTEST(TestCtor);
				OONET_EXECUTE_SUBTEST(TestCtorWrong);
				OONET_EXECUTE_SUBTEST(TestConnect);
				OONET_EXECUTE_SUBTEST(TestConnectConnected);
				OONET_EXECUTE_SUBTEST(TestSend);
				OONET_EXECUTE_SUBTEST(TestSendSpeed);
				OONET_EXECUTE_SUBTEST(TestSendTimeOut);
				OONET_EXECUTE_SUBTEST(TestSendWrongResponse);
				OONET_EXECUTE_SUBTEST(TestReuseDisconnected);
				OONET_EXECUTE_SUBTEST(TestSendServerReset);

				register_test(this);
			}

		} ;	// !test_http_client class
	};	// !test namespace
};	// !oonet namespace

#endif // HTTPCLIENT_TEST_H_DEFINED
