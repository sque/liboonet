#ifndef INETCLIENT_TEST_H_DEFINED
#define INETCLIENT_TEST_H_DEFINED

#include "Test.h"

namespace Slib
{
	class TestInetClient
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTEST(TestTCPCtor, _T("Ctor() IPv4/TCP"));
		SLIB_DECLARESUBTESTEXC(TestUDPCtor, _T("Ctor() IPv4/UDP"), _T("ExceptionAssertationFailed"));
		SLIB_DECLARESUBTESTEXC(TestConnectWrong, _T("Connect() imposible"), _T("ExceptionConnectionRefused"));
		SLIB_DECLARESUBTEST(TestFastConnect, _T("Fast: Create,Connect,Delete"));
		SLIB_DECLARESUBTEST(TestReconnect, _T("Connect() DC and connect"));
		SLIB_DECLARESUBTESTEXC(TestReconnectWrong, _T("Connect() and Connect()"),  _T("ExceptionAlreadyConnected"));
	public:
		// Constructor
		TestInetClient()
			:Test(_T("InetClient"))
		{
			SLIB_REGISTERSUBTEST(TestTCPCtor);
			//SLIB_REGISTERSUBTEST(TestUDPCtor);
			SLIB_REGISTERSUBTEST(TestConnectWrong);
			SLIB_REGISTERSUBTEST(TestFastConnect);
			SLIB_REGISTERSUBTEST(TestReconnect);
			SLIB_REGISTERSUBTEST(TestReconnectWrong);
		}

	} ;	//! TestSocket test
};	//! Slib namespace

#endif // INETCLIENT_TEST_H_DEFINED
