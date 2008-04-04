#ifndef INETCLIENT_TEST_H_DEFINED
#define INETCLIENT_TEST_H_DEFINED

#include "Test.h"

namespace oonet
{
	class test_netstream_threaded
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
		OONET_DECLARESUBTEST(TestReconnectWrong, _T("Connect() and Connect()"));
	public:
		// Constructor
		test_netstream_threaded()
			:Test(_T("netstream_threaded"))
		{
			OONET_REGISTERSUBTEST(TestTCPCtor);
			//OONET_REGISTERSUBTEST(TestUDPCtor);
			OONET_REGISTERSUBTEST(TestConnectWrong);
			OONET_REGISTERSUBTEST(TestFastConnect);
			OONET_REGISTERSUBTEST(TestReconnect);
			OONET_REGISTERSUBTEST(TestReconnectWrong);
		}

	} ;	// !TestInetClient class
};	// !oonet namespace

#endif // INETCLIENT_TEST_H_DEFINED
