#ifndef INETCLIENT_TEST_H_DEFINED
#define INETCLIENT_TEST_H_DEFINED

#include "Test.h"

namespace OONet
{
	class TestInetClient
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestTCPCtor, _T("Ctor() IPv4/TCP"));
		OONET_DECLARESUBTESTEXC(TestUDPCtor, _T("Ctor() IPv4/UDP"), _T("ExceptionAssertationFailed"));
		OONET_DECLARESUBTESTEXC(TestConnectWrong, _T("Connect() imposible"), _T("ExceptionConnectionRefused"));
		OONET_DECLARESUBTEST(TestFastConnect, _T("Fast: Create,Connect,Delete"));
		OONET_DECLARESUBTEST(TestReconnect, _T("Connect() DC and connect"));
		OONET_DECLARESUBTESTEXC(TestReconnectWrong, _T("Connect() and Connect()"),  _T("ExceptionAlreadyConnected"));
	public:
		// Constructor
		TestInetClient()
			:Test(_T("InetClient"))
		{
			OONET_REGISTERSUBTEST(TestTCPCtor);
			//OONET_REGISTERSUBTEST(TestUDPCtor);
			OONET_REGISTERSUBTEST(TestConnectWrong);
			OONET_REGISTERSUBTEST(TestFastConnect);
			OONET_REGISTERSUBTEST(TestReconnect);
			OONET_REGISTERSUBTEST(TestReconnectWrong);
		}

	} ;	// !TestInetClient class
};	// !OONet namespace

#endif // INETCLIENT_TEST_H_DEFINED
