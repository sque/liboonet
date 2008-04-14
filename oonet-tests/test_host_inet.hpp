#ifndef HOSTINET_TEST_H_DEFINED
#define HOSTINET_TEST_H_DEFINED

#include <oonet/binary_data.hpp>
#include "Test.h"

namespace oonet
{
	class TestHostInet
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestDefaultCtor, _T("Default Ctor 0.0.0.0"));
		OONET_DECLARESUBTEST(TestUlongCtor, _T("HostInet() ulong ctor"));
		OONET_DECLARESUBTEST(TestCopyCtor, _T("HostInet() copy ctor"));
		OONET_DECLARESUBTEST(TestCopyOperator, _T("operator= quality test"));
		OONET_DECLARESUBTEST(TestCompOperator, _T("operator== quality test"));
		OONET_DECLARESUBTEST(TestInCompOperator, _T("operator!= quality test"));
		OONET_DECLARESUBTEST(TestGetInetHost, _T("GetInetHost() net-b-order"));
		OONET_DECLARESUBTEST(TestStaticAddress, _T("Static: LOCALHOST, ANY"));

	public:
		// Constructor
		TestHostInet()
			:Test(_T("host_inet"))
		{
			OONET_REGISTERSUBTEST(TestDefaultCtor);
			OONET_REGISTERSUBTEST(TestUlongCtor);
			OONET_REGISTERSUBTEST(TestCopyCtor);
			OONET_REGISTERSUBTEST(TestCopyOperator);
			OONET_REGISTERSUBTEST(TestCompOperator);
			OONET_REGISTERSUBTEST(TestInCompOperator);
			OONET_REGISTERSUBTEST(TestGetInetHost);
			OONET_REGISTERSUBTEST(TestStaticAddress);
		}

	} ;	// !TestHostInet class
};	// !oonet namespace

#endif // HOSTINET_TEST_H_DEFINED
