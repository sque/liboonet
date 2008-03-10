#ifndef HOSTINET_TEST_H_DEFINED
#define HOSTINET_TEST_H_DEFINED

#include "BinaryData.h"
#include "Test.h"

namespace Slib
{
	class TestHostInet
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTEST(TestDefaultCtor, _T("Default Ctor 0.0.0.0"));
		SLIB_DECLARESUBTEST(TestUlongCtor, _T("HostInet() ulong ctor"));
		SLIB_DECLARESUBTEST(TestCopyCtor, _T("HostInet() copy ctor"));
		SLIB_DECLARESUBTEST(TestCopyOperator, _T("operator= quality test"));
		SLIB_DECLARESUBTEST(TestCompOperator, _T("operator== quality test"));
		SLIB_DECLARESUBTEST(TestInCompOperator, _T("operator!= quality test"));
		SLIB_DECLARESUBTEST(TestGetInetHost, _T("GetInetHost() net-b-order"));
		SLIB_DECLARESUBTEST(TestStaticAddress, _T("Static: LOCALHOST, ANY"));

	public:
		// Constructor
		TestHostInet()
			:Test(_T("HostInet"))
		{
			SLIB_REGISTERSUBTEST(TestDefaultCtor);
			SLIB_REGISTERSUBTEST(TestUlongCtor);
			SLIB_REGISTERSUBTEST(TestCopyCtor);
			SLIB_REGISTERSUBTEST(TestCopyOperator);
			SLIB_REGISTERSUBTEST(TestCompOperator);
			SLIB_REGISTERSUBTEST(TestInCompOperator);
			SLIB_REGISTERSUBTEST(TestGetInetHost);
			SLIB_REGISTERSUBTEST(TestStaticAddress);
		}

	} ;	//! TestPortInet test
};	//! Slib namespace

#endif // HOSTINET_TEST_H_DEFINED
