#ifndef HTTPCLIENT_TEST_H_DEFINED
#define HTTPCLIENT_TEST_H_DEFINED

#include "Test.h"

namespace Slib
{
	class TestHTTPClient
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTEST(TestCtor, _T("Ctor() default"));
		SLIB_DECLARESUBTESTEXC(TestCtorWrong, _T("Ctor() on imposible svr"), _T("ExceptionConnectionRefused"));
		SLIB_DECLARESUBTEST(TestChangeHost, _T("ChangeHost() on not con"));
		SLIB_DECLARESUBTEST(TestChangeHostConnected, _T("ChangeHost() on connected"));
		SLIB_DECLARESUBTEST(TestReconnect, _T("Reconnect() check quality"));
		SLIB_DECLARESUBTEST(TestReconnectWrong, _T("Reconnect() on no svr"));
		SLIB_DECLARESUBTEST(TestSend, _T("Send() quality"));
		SLIB_DECLARESUBTESTEXC(TestSendTimeOut, _T("Send() time out"), _T("ExceptionTimeOut"));
		SLIB_DECLARESUBTESTEXC(TestSendWrongResponse, _T("Send() wrong response"), _T("ExceptionWrongFormat"));
		SLIB_DECLARESUBTEST(TestReuseDisconnected, _T("Reuse disconencted"));
	public:
		// Constructor
		TestHTTPClient()
			:Test(_T("HTTP::Client"))
		{
			SLIB_REGISTERSUBTEST(TestCtor);
			SLIB_REGISTERSUBTEST(TestCtorWrong);
			SLIB_REGISTERSUBTEST(TestChangeHost);
			SLIB_REGISTERSUBTEST(TestChangeHostConnected);
			SLIB_REGISTERSUBTEST(TestReconnect);
			SLIB_REGISTERSUBTEST(TestReconnectWrong);
			SLIB_REGISTERSUBTEST(TestSend);
			SLIB_REGISTERSUBTEST(TestSendTimeOut);
			SLIB_REGISTERSUBTEST(TestSendWrongResponse);
			SLIB_REGISTERSUBTEST(TestReuseDisconnected);
		}

	} ;	//! TestHTTPClient test
};	//! Slib namespace

#endif // HTTPCLIENT_TEST_H_DEFINED
