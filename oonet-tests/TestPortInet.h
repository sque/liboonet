#ifndef PORTINET_TEST_H_DEFINED
#define PORTINET_TEST_H_DEFINED

#include "BinaryData.h"
#include "Test.h"

namespace Slib
{
	class TestPortInet
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTEST(TestDefaultCtor, _T("Default Ctor must be 0"));
		SLIB_DECLARESUBTEST(TestUshortCtor,  _T("PortInet(ushort) ctor") );
		SLIB_DECLARESUBTEST(TestCopyConstructor,  _T("PortInet() copy ctor") );
		SLIB_DECLARESUBTEST(TestCopyOperator,  _T("operator= quality test") );
		SLIB_DECLARESUBTEST(TestComparisonOperator,  _T("operator== quality test") );
		SLIB_DECLARESUBTEST(TestInComparisonOperator,  _T("operator!= quality test") );
		SLIB_DECLARESUBTEST(TestGetInetPort, _T("GetInetPort() net-b-order"));
	public:
		// Constructor
		TestPortInet()
			:Test(_T("PortInet"))
		{
			SLIB_REGISTERSUBTEST(TestDefaultCtor);
			SLIB_REGISTERSUBTEST(TestUshortCtor);
			SLIB_REGISTERSUBTEST(TestCopyConstructor);
			SLIB_REGISTERSUBTEST(TestCopyOperator);
			SLIB_REGISTERSUBTEST(TestComparisonOperator);
			SLIB_REGISTERSUBTEST(TestInComparisonOperator);
			SLIB_REGISTERSUBTEST(TestGetInetPort);
		}

	} ;	//! TestPortInet test
};	//! Slib namespace

#endif // PORTINET_TEST_H_DEFINED
