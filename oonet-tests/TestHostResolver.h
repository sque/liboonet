#ifndef HOSTRESOLVER_TEST_H_DEFINED
#define HOSTRESOLVER_TEST_H_DEFINED

#include "binary_data.hpp"
#include "Test.h"

namespace oonet
{
	class TestHostResolver
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTESTEXC(TestErrorResolv, _T("Resolve koukouroukou"), _T("ExceptionServerNotFound"));
		OONET_DECLARESUBTEST(TestLocalhost, _T("Resolve localhost"));
		OONET_DECLARESUBTEST(TestResolveIPs, _T("Resolve ready ips"));
		OONET_DECLARESUBTEST(TestCopyCtor, _T("Copy constructor"));
		OONET_DECLARESUBTESTEXC(TestGetAddressOver, _T("getAddress() overflow"), _T("ExceptionNotFound"));
	public:
		// Constructor
		TestHostResolver()
			:Test(_T("HostResolver"))
		{
			OONET_REGISTERSUBTEST(TestErrorResolv);
			OONET_REGISTERSUBTEST(TestLocalhost);
			OONET_REGISTERSUBTEST(TestResolveIPs);
			OONET_REGISTERSUBTEST(TestCopyCtor);
			OONET_REGISTERSUBTEST(TestGetAddressOver);
		}

	} ;	// !TestHostResolver class
};	// !oonet namespace

#endif // HOSTRESOLVER_TEST_H_DEFINED

