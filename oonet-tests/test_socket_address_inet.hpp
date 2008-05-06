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
			OONET_DECLARESUBTEST(TestCtor, "Ctor() default");
			OONET_DECLARESUBTEST(TestHostPortCtor, "Ctor() Host,Port");
			OONET_DECLARESUBTEST(TestResolverPortCtor, "Ctor() Resolver,Port");
			OONET_DECLARESUBTEST(TestSockAddrCtor, "Ctor() from sockaddr");
			OONET_DECLARESUBTESTEXC(TestSockAddrNonInetCtor, "Ctor() from non-inet", "ExceptionAssertationFailed");
			OONET_DECLARESUBTEST(TestCopyCtor, "Ctor() copy");
			OONET_DECLARESUBTEST(TestDefaultValues, "Default values");
			OONET_DECLARESUBTEST(TestCopyOperator, "operator= quality test");
			OONET_DECLARESUBTEST(TestCompOperator, "operator== quality test");
			OONET_DECLARESUBTEST(TestInCompOperator, "operator!= quality test");
			OONET_DECLARESUBTEST(TestSetHost, "setHostInet() quality test");
			OONET_DECLARESUBTEST(TestSetPost, "setPostInet() quality test");

		public:
			// Constructor
			test_socket_address_inet()
				:test_set("socket_address_inet")
			{
				OONET_REGISTERSUBTEST(TestCtor);
				OONET_REGISTERSUBTEST(TestHostPortCtor);
				OONET_REGISTERSUBTEST(TestResolverPortCtor);
				OONET_REGISTERSUBTEST(TestSockAddrCtor);
				OONET_REGISTERSUBTEST(TestSockAddrNonInetCtor);
				OONET_REGISTERSUBTEST(TestCopyCtor);
				OONET_REGISTERSUBTEST(TestDefaultValues);
				OONET_REGISTERSUBTEST(TestCopyOperator);
				OONET_REGISTERSUBTEST(TestSetHost);
				OONET_REGISTERSUBTEST(TestSetPost);
				OONET_REGISTERSUBTEST(TestCompOperator);
				OONET_REGISTERSUBTEST(TestInCompOperator);

				register_test(this);
			}

		} ;	// !test_socket_address_inet class
	}	// !test namespace
};	// !oonet namespace

#endif // HOSTRESOLVER_TEST_H_DEFINED

