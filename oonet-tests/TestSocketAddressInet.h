#ifndef HOSTRESOLVER_TEST_H_DEFINED
#define HOSTRESOLVER_TEST_H_DEFINED

#include "BinaryData.h"
#include "Test.h"

namespace Slib
{
	class TestSocketAddressInet
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTEST(TestCtor, _T("Ctor() default"));
		SLIB_DECLARESUBTEST(TestHostPortCtor, _T("Ctor() Host,Port"));
		SLIB_DECLARESUBTEST(TestResolverPortCtor, _T("Ctor() Resolver,Port"));
		SLIB_DECLARESUBTEST(TestSockAddrCtor, _T("Ctor() from sockaddr"));
		SLIB_DECLARESUBTESTEXC(TestSockAddrNonInetCtor, _T("Ctor() from non-inet"),_T("ExceptionAssertationFailed"));
		SLIB_DECLARESUBTEST(TestCopyCtor, _T("Ctor() copy"));
		SLIB_DECLARESUBTEST(TestDefaultValues, _T("Default values"));
		SLIB_DECLARESUBTEST(TestCopyOperator, _T("operator= quality test"));
		SLIB_DECLARESUBTEST(TestCompOperator, _T("operator== quality test"));
		SLIB_DECLARESUBTEST(TestInCompOperator, _T("operator!= quality test"));
		SLIB_DECLARESUBTEST(TestSetHost, _T("setHostInet() quality test"));
		SLIB_DECLARESUBTEST(TestSetPost, _T("setPostInet() quality test"));

	public:
		// Constructor
		TestSocketAddressInet()
			:Test(_T("SocketAddressInet"))
		{
			SLIB_REGISTERSUBTEST(TestCtor);
			SLIB_REGISTERSUBTEST(TestHostPortCtor);
			SLIB_REGISTERSUBTEST(TestResolverPortCtor);
			SLIB_REGISTERSUBTEST(TestSockAddrCtor);
			SLIB_REGISTERSUBTEST(TestSockAddrNonInetCtor);
			SLIB_REGISTERSUBTEST(TestCopyCtor);
			SLIB_REGISTERSUBTEST(TestDefaultValues);
			SLIB_REGISTERSUBTEST(TestCopyOperator);
			SLIB_REGISTERSUBTEST(TestSetHost);
			SLIB_REGISTERSUBTEST(TestSetPost);
			SLIB_REGISTERSUBTEST(TestCompOperator);
			SLIB_REGISTERSUBTEST(TestInCompOperator);
		}

	} ;	//! TestSocketAddressInet test
};	//! Slib namespace

#endif // HOSTRESOLVER_TEST_H_DEFINED

