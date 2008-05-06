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
			OONET_DECLARESUBTEST(TestCtor, "ctor() default");
			OONET_DECLARESUBTESTEXC(TestCtorWrong, "ctor() on imposible svr", "ExceptionConnectionRefused");
			OONET_DECLARESUBTEST(TestConnect, "connect() on not con");
			OONET_DECLARESUBTEST(TestConnectConnected, "connect() on connected");
			OONET_DECLARESUBTEST(TestSend, "send() quality");
			OONET_DECLARESUBTEST(TestSendSpeed, "send() speed 50MB/1k block");
			OONET_DECLARESUBTESTEXC(TestSendTimeOut, "send() time out", "ExceptionTimeOut");
			OONET_DECLARESUBTESTEXC(TestSendWrongResponse, "send() wrong response", "ExceptionWrongFormat");
			OONET_DECLARESUBTEST(TestReuseDisconnected, "Reuse disconencted");
			OONET_DECLARESUBTESTEXC(TestSendServerReset, "send() server resets", "ExceptionIncomplete");
		public:
			// Constructor
			test_http_client()
				:test_set("http::client")
			{
				OONET_REGISTERSUBTEST(TestCtor);
				OONET_REGISTERSUBTEST(TestCtorWrong);
				OONET_REGISTERSUBTEST(TestConnect);
				OONET_REGISTERSUBTEST(TestConnectConnected);
				OONET_REGISTERSUBTEST(TestSend);
				OONET_REGISTERSUBTEST(TestSendSpeed);
				OONET_REGISTERSUBTEST(TestSendTimeOut);
				OONET_REGISTERSUBTEST(TestSendWrongResponse);
				OONET_REGISTERSUBTEST(TestReuseDisconnected);
				OONET_REGISTERSUBTEST(TestSendServerReset);

				register_test(this);
			}

		} ;	// !test_http_client class
	};	// !test namespace
};	// !oonet namespace

#endif // HTTPCLIENT_TEST_H_DEFINED
