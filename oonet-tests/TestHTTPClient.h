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
		OONET_DECLARESUBTEST(TestChangeHost, _T("ChangeHost() on not con"));
		OONET_DECLARESUBTEST(TestChangeHostConnected, _T("ChangeHost() on connected"));
		OONET_DECLARESUBTEST(TestReconnect, _T("Reconnect() check quality"));
		OONET_DECLARESUBTEST(TestReconnectWrong, _T("Reconnect() on no svr"));
		OONET_DECLARESUBTEST(TestSend, _T("Send() quality"));
		OONET_DECLARESUBTESTEXC(TestSendTimeOut, _T("Send() time out"), _T("ExceptionTimeOut"));
		OONET_DECLARESUBTESTEXC(TestSendWrongResponse, _T("Send() wrong response"), _T("ExceptionWrongFormat"));
		OONET_DECLARESUBTEST(TestReuseDisconnected, _T("Reuse disconencted"));
	public:
		// Constructor
		TestHTTPClient()
			:Test(_T("HTTP::Client"))
		{
			OONET_REGISTERSUBTEST(TestCtor);
			OONET_REGISTERSUBTEST(TestCtorWrong);
			OONET_REGISTERSUBTEST(TestChangeHost);
			OONET_REGISTERSUBTEST(TestChangeHostConnected);
			OONET_REGISTERSUBTEST(TestReconnect);
			OONET_REGISTERSUBTEST(TestReconnectWrong);
			OONET_REGISTERSUBTEST(TestSend);
			OONET_REGISTERSUBTEST(TestSendTimeOut);
			OONET_REGISTERSUBTEST(TestSendWrongResponse);
			OONET_REGISTERSUBTEST(TestReuseDisconnected);
		}

	} ;	// !TestHTTPClient class
};	// !OONet namespace

#endif // HTTPCLIENT_TEST_H_DEFINED
