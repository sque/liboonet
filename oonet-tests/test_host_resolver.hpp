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
			OONET_DECLARESUBTESTEXC(TestErrorResolv, "Resolve koukouroukou", "ExceptionServerNotFound");
			OONET_DECLARESUBTEST(TestLocalhost, "Resolve localhost");
			OONET_DECLARESUBTEST(TestResolveIPs, "Resolve ready ips");
			OONET_DECLARESUBTEST(TestCopyCtor, "Copy constructor");
			OONET_DECLARESUBTESTEXC(TestGetAddressOver, "getAddress() overflow", "ExceptionNotFound");
		public:
			// Constructor
			test_host_resolver()
				:test_set("host_resolver")
			{
				OONET_REGISTERSUBTEST(TestErrorResolv);
				OONET_REGISTERSUBTEST(TestLocalhost);
				OONET_REGISTERSUBTEST(TestResolveIPs);
				OONET_REGISTERSUBTEST(TestCopyCtor);
				OONET_REGISTERSUBTEST(TestGetAddressOver);

				register_test(this);
			}

		} ;	// !test_host_resolver class
	}	// !test namespace
};	// !oonet namespace

#endif // HOSTRESOLVER_TEST_H_DEFINED

