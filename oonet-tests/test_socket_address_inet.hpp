#ifndef HOSTRESOLVER_TEST_H_DEFINED
#define HOSTRESOLVER_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_socket_address_inet
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARE_SUBTEST(TestCtor, "Ctor() default");
			OONET_DECLARE_SUBTEST(TestHostPortCtor, "Ctor() Host,Port");
			OONET_DECLARE_SUBTEST(TestResolverPortCtor, "Ctor() Resolver,Port");
			OONET_DECLARE_SUBTEST(TestSockAddrCtor, "Ctor() from sockaddr");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestSockAddrNonInetCtor, "Ctor() from non-inet", "ExceptionAssertationFailed");
			OONET_DECLARE_SUBTEST(TestCopyCtor, "Ctor() copy");
			OONET_DECLARE_SUBTEST(TestDefaultValues, "Default values");
			OONET_DECLARE_SUBTEST(TestCopyOperator, "operator= quality test");
			OONET_DECLARE_SUBTEST(TestCompOperator, "operator== quality test");
			OONET_DECLARE_SUBTEST(TestInCompOperator, "operator!= quality test");
			OONET_DECLARE_SUBTEST(TestSetHost, "setHostInet() quality test");
			OONET_DECLARE_SUBTEST(TestSetPost, "setPostInet() quality test");

		public:
			// Constructor
			test_socket_address_inet()
				:test_set("socket_address_inet")
			{
				OONET_EXECUTE_SUBTEST(TestCtor);
				OONET_EXECUTE_SUBTEST(TestHostPortCtor);
				OONET_EXECUTE_SUBTEST(TestResolverPortCtor);
				OONET_EXECUTE_SUBTEST(TestSockAddrCtor);
				OONET_EXECUTE_SUBTEST(TestSockAddrNonInetCtor);
				OONET_EXECUTE_SUBTEST(TestCopyCtor);
				OONET_EXECUTE_SUBTEST(TestDefaultValues);
				OONET_EXECUTE_SUBTEST(TestCopyOperator);
				OONET_EXECUTE_SUBTEST(TestSetHost);
				OONET_EXECUTE_SUBTEST(TestSetPost);
				OONET_EXECUTE_SUBTEST(TestCompOperator);
				OONET_EXECUTE_SUBTEST(TestInCompOperator);

				register_test(this);
			}

		} ;	// !test_socket_address_inet class
	}	// !test namespace
};	// !oonet namespace

#endif // HOSTRESOLVER_TEST_H_DEFINED

