#ifndef INETCLIENT_TEST_H_DEFINED
#define INETCLIENT_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_netstream_threaded
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARE_SUBTEST(TestCtor, "Ctor()");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestConnectWrong, "Connect() imposible", "ExceptionConnectionRefused");
			OONET_DECLARE_SUBTEST(TestFastConnect, "Fast: Create,Connect,Delete");
			OONET_DECLARE_SUBTEST(TestConDCCon, "Connect() DC and connect");
			OONET_DECLARE_SUBTEST(TestReconnect, "Connect() and Connect()");
			OONET_DECLARE_SUBTEST(TestEventQuality, "on_XXX() quality test");
		public:
			// Constructor
			test_netstream_threaded()
				:test_set("netstream_threaded")
			{
				OONET_EXECUTE_SUBTEST(TestCtor);
				OONET_EXECUTE_SUBTEST(TestConnectWrong);
				OONET_EXECUTE_SUBTEST(TestFastConnect);
				OONET_EXECUTE_SUBTEST(TestConDCCon);
				OONET_EXECUTE_SUBTEST(TestReconnect);
				OONET_EXECUTE_SUBTEST(TestEventQuality);

				register_test(this);
			}

		} ;	// !test_netstream_threaded class
	}	// !test namespace
};	// !oonet namespace

#endif // INETCLIENT_TEST_H_DEFINED
