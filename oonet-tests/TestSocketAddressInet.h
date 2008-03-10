#ifndef HOSTRESOLVER_TEST_H_DEFINED
#define HOSTRESOLVER_TEST_H_DEFINED

#include "BinaryData.h"
#include "Test.h"

namespace OONet
{
	class TestSocketAddressInet
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestCtor, _T("Ctor() default"));
		OONET_DECLARESUBTEST(TestHostPortCtor, _T("Ctor() Host,Port"));
		OONET_DECLARESUBTEST(TestResolverPortCtor, _T("Ctor() Resolver,Port"));
		OONET_DECLARESUBTEST(TestSockAddrCtor, _T("Ctor() from sockaddr"));
		OONET_DECLARESUBTESTEXC(TestSockAddrNonInetCtor, _T("Ctor() from non-inet"),_T("ExceptionAssertationFailed"));
		OONET_DECLARESUBTEST(TestCopyCtor, _T("Ctor() copy"));
		OONET_DECLARESUBTEST(TestDefaultValues, _T("Default values"));
		OONET_DECLARESUBTEST(TestCopyOperator, _T("operator= quality test"));
		OONET_DECLARESUBTEST(TestCompOperator, _T("operator== quality test"));
		OONET_DECLARESUBTEST(TestInCompOperator, _T("operator!= quality test"));
		OONET_DECLARESUBTEST(TestSetHost, _T("setHostInet() quality test"));
		OONET_DECLARESUBTEST(TestSetPost, _T("setPostInet() quality test"));

	public:
		// Constructor
		TestSocketAddressInet()
			:Test(_T("SocketAddressInet"))
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
		}

	} ;	// !TestSocketAddressInet class
};	// !OONet namespace

#endif // HOSTRESOLVER_TEST_H_DEFINED

