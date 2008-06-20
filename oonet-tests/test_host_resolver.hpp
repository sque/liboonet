#ifndef HOSTRESOLVER_TEST_H_DEFINED
#define HOSTRESOLVER_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_host_resolver
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestErrorResolv, "Resolve koukouroukou", "ExceptionServerNotFound");
			OONET_DECLARE_SUBTEST(TestLocalhost, "Resolve localhost");
			OONET_DECLARE_SUBTEST(TestResolveIPs, "Resolve ready ips");
			OONET_DECLARE_SUBTEST(TestCopyCtor, "Copy constructor");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestGetAddressOver, "getAddress() overflow", "ExceptionNotFound");
		public:
			// Constructor
			test_host_resolver()
				:test_set("host_resolver")
			{
				OONET_EXECUTE_SUBTEST(TestErrorResolv);
				OONET_EXECUTE_SUBTEST(TestLocalhost);
				OONET_EXECUTE_SUBTEST(TestResolveIPs);
				OONET_EXECUTE_SUBTEST(TestCopyCtor);
				OONET_EXECUTE_SUBTEST(TestGetAddressOver);

				register_test(this);
			}

		} ;	// !test_host_resolver class
	}	// !test namespace
};	// !oonet namespace

#endif // HOSTRESOLVER_TEST_H_DEFINED

