#ifndef HOSTRESOLVER_TEST_H_DEFINED
#define HOSTRESOLVER_TEST_H_DEFINED

#include "BinaryData.h"
#include "Test.h"

namespace Slib
{
	class TestHostResolver
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTESTEXC(TestErrorResolv, _T("Resolve koukouroukou"), _T("ExceptionServerNotFound"));
		SLIB_DECLARESUBTEST(TestLocalhost, _T("Resolve localhost"));
		SLIB_DECLARESUBTEST(TestResolveIPs, _T("Resolve ready ips"));
		SLIB_DECLARESUBTEST(TestCopyCtor, _T("Copy constructor"));
		SLIB_DECLARESUBTESTEXC(TestGetAddressOver, _T("getAddress() overflow"), _T("ExceptionNotFound"));
	public:
		// Constructor
		TestHostResolver()
			:Test(_T("HostResolver"))
		{
			SLIB_REGISTERSUBTEST(TestErrorResolv);
			SLIB_REGISTERSUBTEST(TestLocalhost);
			SLIB_REGISTERSUBTEST(TestResolveIPs);
			SLIB_REGISTERSUBTEST(TestCopyCtor);
			SLIB_REGISTERSUBTEST(TestGetAddressOver);
		}

	} ;	//! TestMutex test
};	//! Slib namespace

#endif // HOSTRESOLVER_TEST_H_DEFINED

