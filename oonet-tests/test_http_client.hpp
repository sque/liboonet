#ifndef HTTPCLIENT_TEST_H_DEFINED
#define HTTPCLIENT_TEST_H_DEFINED

#include "Test.h"

namespace oonet
{
	class TestHTTPClient
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestCtor, _T("ctor() default"));
		OONET_DECLARESUBTESTEXC(TestCtorWrong, _T("ctor() on imposible svr"), _T("ExceptionConnectionRefused"));
		OONET_DECLARESUBTEST(TestConnect, _T("connect() on not con"));
		OONET_DECLARESUBTEST(TestConnectConnected, _T("connect() on connected"));
		OONET_DECLARESUBTEST(TestSend, _T("send() quality"));
		OONET_DECLARESUBTEST(TestSendSpeed, _T("send() speed 50MB/1k block"));
		OONET_DECLARESUBTESTEXC(TestSendTimeOut, _T("send() time out"), _T("ExceptionTimeOut"));
		OONET_DECLARESUBTESTEXC(TestSendWrongResponse, _T("send() wrong response"), _T("ExceptionWrongFormat"));
		OONET_DECLARESUBTEST(TestReuseDisconnected, _T("Reuse disconencted"));
		OONET_DECLARESUBTESTEXC(TestSendServerReset, _T("send() server resets"), "ExceptionIncomplete");
	public:
		// Constructor
		TestHTTPClient()
			:Test(_T("http::client"))
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
		}

	} ;	// !TestHTTPClient class
};	// !oonet namespace

#endif // HTTPCLIENT_TEST_H_DEFINED
