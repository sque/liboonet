#ifndef PORTINET_TEST_H_DEFINED
#define PORTINET_TEST_H_DEFINED

#include <oonet/binary_data.hpp>
#include "Test.h"

namespace oonet
{
	class TestPortInet
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestDefaultCtor, _T("Default Ctor must be 0"));
		OONET_DECLARESUBTEST(TestUshortCtor,  _T("PortInet(ushort) ctor") );
		OONET_DECLARESUBTEST(TestCopyConstructor,  _T("PortInet() copy ctor") );
		OONET_DECLARESUBTEST(TestCopyOperator,  _T("operator= quality test") );
		OONET_DECLARESUBTEST(TestComparisonOperator,  _T("operator== quality test") );
		OONET_DECLARESUBTEST(TestInComparisonOperator,  _T("operator!= quality test") );
		OONET_DECLARESUBTEST(TestGetInetPort, _T("GetInetPort() net-b-order"));
	public:
		// Constructor
		TestPortInet()
			:Test(_T("port_inet"))
		{
			OONET_REGISTERSUBTEST(TestDefaultCtor);
			OONET_REGISTERSUBTEST(TestUshortCtor);
			OONET_REGISTERSUBTEST(TestCopyConstructor);
			OONET_REGISTERSUBTEST(TestCopyOperator);
			OONET_REGISTERSUBTEST(TestComparisonOperator);
			OONET_REGISTERSUBTEST(TestInComparisonOperator);
			OONET_REGISTERSUBTEST(TestGetInetPort);
		}

	} ;	// !TestPortInet class
};	// !oonet namespace

#endif // PORTINET_TEST_H_DEFINED
