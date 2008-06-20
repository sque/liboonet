#ifndef HOSTINET_TEST_H_DEFINED
#define HOSTINET_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_host_inet
			: public test_set
		{
		public:

			////////////////////////////
			// SUB TESTS
			OONET_DECLARE_SUBTEST(TestDefaultCtor, _T("Default Ctor 0.0.0.0"));
			OONET_DECLARE_SUBTEST(TestUlongCtor, _T("HostInet() ulong ctor"));
			OONET_DECLARE_SUBTEST(TestCopyCtor, _T("HostInet() copy ctor"));
			OONET_DECLARE_SUBTEST(TestCopyOperator, _T("operator= quality test"));
			OONET_DECLARE_SUBTEST(TestCompOperator, _T("operator== quality test"));
			OONET_DECLARE_SUBTEST(TestInCompOperator, _T("operator!= quality test"));
			OONET_DECLARE_SUBTEST(TestGetInetHost, _T("GetInetHost() net-b-order"));
			OONET_DECLARE_SUBTEST(TestStaticAddress, _T("Static: LOCALHOST, ANY"));

		public:
			// Constructor
			test_host_inet()
				:test_set("host_inet")
			{
				OONET_EXECUTE_SUBTEST(TestDefaultCtor);
				OONET_EXECUTE_SUBTEST(TestUlongCtor);
				OONET_EXECUTE_SUBTEST(TestCopyCtor);
				OONET_EXECUTE_SUBTEST(TestCopyOperator);
				OONET_EXECUTE_SUBTEST(TestCompOperator);
				OONET_EXECUTE_SUBTEST(TestInCompOperator);
				OONET_EXECUTE_SUBTEST(TestGetInetHost);
				OONET_EXECUTE_SUBTEST(TestStaticAddress);

				register_test(this);
			}
		};	// !test_host_inet class
	}	// !test namespace
}	// !oonet namespace

#endif // HOSTINET_TEST_H_DEFINED
