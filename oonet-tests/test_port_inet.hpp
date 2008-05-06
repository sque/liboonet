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
			OONET_DECLARESUBTEST(TestDefaultCtor, "Default Ctor must be 0");
			OONET_DECLARESUBTEST(TestUshortCtor, "PortInet(ushort) ctor");
			OONET_DECLARESUBTEST(TestCopyConstructor, "PortInet() copy ctor");
			OONET_DECLARESUBTEST(TestCopyOperator, "operator= quality test");
			OONET_DECLARESUBTEST(TestComparisonOperator, "operator== quality test");
			OONET_DECLARESUBTEST(TestInComparisonOperator, "operator!= quality test");
			OONET_DECLARESUBTEST(TestGetInetPort, "GetInetPort() net-b-order");
		public:
			// Constructor
			test_port_inet()
				:test_set("port_inet")
			{
				OONET_REGISTERSUBTEST(TestDefaultCtor);
				OONET_REGISTERSUBTEST(TestUshortCtor);
				OONET_REGISTERSUBTEST(TestCopyConstructor);
				OONET_REGISTERSUBTEST(TestCopyOperator);
				OONET_REGISTERSUBTEST(TestComparisonOperator);
				OONET_REGISTERSUBTEST(TestInComparisonOperator);
				OONET_REGISTERSUBTEST(TestGetInetPort);

				register_test(this);
			}

		} ;	// !test_port_inet class
	}	// !test namespace
};	// !oonet namespace

#endif // PORTINET_TEST_H_DEFINED
