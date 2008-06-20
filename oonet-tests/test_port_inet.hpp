#ifndef PORTINET_TEST_H_DEFINED
#define PORTINET_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_port_inet
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARE_SUBTEST(TestDefaultCtor, "Default Ctor must be 0");
			OONET_DECLARE_SUBTEST(TestUshortCtor, "PortInet(ushort) ctor");
			OONET_DECLARE_SUBTEST(TestCopyConstructor, "PortInet() copy ctor");
			OONET_DECLARE_SUBTEST(TestCopyOperator, "operator= quality test");
			OONET_DECLARE_SUBTEST(TestComparisonOperator, "operator== quality test");
			OONET_DECLARE_SUBTEST(TestInComparisonOperator, "operator!= quality test");
			OONET_DECLARE_SUBTEST(TestGetInetPort, "GetInetPort() net-b-order");
		public:
			// Constructor
			test_port_inet()
				:test_set("port_inet")
			{
				OONET_EXECUTE_SUBTEST(TestDefaultCtor);
				OONET_EXECUTE_SUBTEST(TestUshortCtor);
				OONET_EXECUTE_SUBTEST(TestCopyConstructor);
				OONET_EXECUTE_SUBTEST(TestCopyOperator);
				OONET_EXECUTE_SUBTEST(TestComparisonOperator);
				OONET_EXECUTE_SUBTEST(TestInComparisonOperator);
				OONET_EXECUTE_SUBTEST(TestGetInetPort);

				register_test(this);
			}

		} ;	// !test_port_inet class
	}	// !test namespace
};	// !oonet namespace

#endif // PORTINET_TEST_H_DEFINED
