#ifndef HTTPCLIENT_TEST_H_DEFINED
#define HTTPCLIENT_TEST_H_DEFINED

#include "Test.h"

namespace OONet
{
	class TestHTTPClient
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestCtor, _T("Ctor() default"));
		OONET_DECLARESUBTESTEXC(TestCtorWrong, _T("Ctor() on imposible svr"), _T("ExceptionConnectionRefused"));
		OONET_DECLARESUBTEST(TestConnect, _T("Connect() on not con"));
		OONET_DECLARESUBTEST(TestConnectConnected, _T("Connect() on connected"));
		OONET_DECLARESUBTEST(TestSend, _T("Send() quality"));
		OONET_DECLARESUBTESTEXC(TestSendTimeOut, _T("Send() time out"), _T("ExceptionTimeOut"));
		OONET_DECLARESUBTESTEXC(TestSendWrongResponse, _T("Send() wrong response"), _T("ExceptionWrongFormat"));
		OONET_DECLARESUBTEST(TestReuseDisconnected, _T("Reuse disconencted"));
		OONET_DECLARESUBTESTEXC(TestSendServerReset, _T("Send() server resets"), "ExceptionIncomplete");
	public:
		// Constructor
		TestHTTPClient()
			:Test(_T("HTTP::Client"))
		{
			OONET_REGISTERSUBTEST(TestCtor);
			OONET_REGISTERSUBTEST(TestCtorWrong);
			OONET_REGISTERSUBTEST(TestConnect);
			OONET_REGISTERSUBTEST(TestConnectConnected);
			OONET_REGISTERSUBTEST(TestSend);
			OONET_REGISTERSUBTEST(TestSendTimeOut);
			OONET_REGISTERSUBTEST(TestSendWrongResponse);
			OONET_REGISTERSUBTEST(TestReuseDisconnected);
			OONET_REGISTERSUBTEST(TestSendServerReset);
		}

	} ;	// !TestHTTPClient class
};	// !OONet namespace

#endif // HTTPCLIENT_TEST_H_DEFINED
