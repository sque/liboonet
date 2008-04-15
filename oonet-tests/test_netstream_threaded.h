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
		OONET_DECLARESUBTEST(TestCtor, "Ctor()");
		OONET_DECLARESUBTESTEXC(TestConnectWrong, "Connect() imposible", "ExceptionConnectionRefused");
		OONET_DECLARESUBTEST(TestFastConnect, "Fast: Create,Connect,Delete");
		OONET_DECLARESUBTEST(TestConDCCon, "Connect() DC and connect");
		OONET_DECLARESUBTEST(TestReconnect, "Connect() and Connect()");
		OONET_DECLARESUBTEST(TestEventQuality, "on_XXX() quality test");
	public:
		// Constructor
		test_netstream_threaded()
			:Test(_T("netstream_threaded"))
		{
			OONET_REGISTERSUBTEST(TestCtor);
			OONET_REGISTERSUBTEST(TestConnectWrong);
			OONET_REGISTERSUBTEST(TestFastConnect);
			OONET_REGISTERSUBTEST(TestConDCCon);
			OONET_REGISTERSUBTEST(TestReconnect);
			OONET_REGISTERSUBTEST(TestEventQuality);
		}

	} ;	// !TestInetClient class
};	// !oonet namespace

#endif // INETCLIENT_TEST_H_DEFINED
