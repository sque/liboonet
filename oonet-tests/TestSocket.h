#ifndef SOCKET_TEST_H_DEFINED
#define SOCKET_TEST_H_DEFINED

#include "Test.h"

namespace Slib
{
	class TestSocket
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		SLIB_DECLARESUBTEST(TestTCPCtor, _T("Ctor() IPv4/TCP"));
		SLIB_DECLARESUBTEST(TestUDPCtor, _T("Ctor() IPv4/UDP"));

#if SLIB_OS == SLIB_OS_WIN32
		SLIB_DECLARESUBTEST(TestRAWCtor, _T("Ctor() IPv4/RAW"));
#else
		SLIB_DECLARESUBTESTEXC(TestRAWCtor, _T("Ctor() IPv4/RAW"), _T("ExceptionNotSupported"));
#endif


#if SLIB_OS == SLIB_OS_WIN32
		SLIB_DECLARESUBTESTEXC(TestWhateverCtor, _T("Ctor() IPv4/Invalid"), _T("ExceptionNotSupported"));
#else
        SLIB_DECLARESUBTESTEXC(TestWhateverCtor, _T("Ctor() IPv4/Invalid"), _T("ExceptionWrongArgument"));
#endif
		SLIB_DECLARESUBTEST(TestTCPConnect, _T("Connect() IPv4/TCP"));
		SLIB_DECLARESUBTESTEXC(TestTCPConnectWrong, _T("Connect() wrong"), _T("ExceptionConnectionRefused"));
		SLIB_DECLARESUBTESTEXC(TestBindWrong, _T("Bind() wrong"), _T("ExceptionAddressNotAvailable"));
		SLIB_DECLARESUBTESTEXC(TestBindRebind, _T("Bind() twice"), _T("ExceptionWrongArgument"));
		SLIB_DECLARESUBTEST(TestBind, _T("Bind() normal"));
	public:
		// Constructor
		TestSocket()
			:Test(_T("Socket"))
		{
			SLIB_REGISTERSUBTEST(TestTCPCtor);
			SLIB_REGISTERSUBTEST(TestUDPCtor);
			SLIB_REGISTERSUBTEST(TestRAWCtor);
			SLIB_REGISTERSUBTEST(TestWhateverCtor);
			SLIB_REGISTERSUBTEST(TestTCPConnect);
			SLIB_REGISTERSUBTEST(TestTCPConnectWrong);
			SLIB_REGISTERSUBTEST(TestBindWrong);
			SLIB_REGISTERSUBTEST(TestBindRebind);
			SLIB_REGISTERSUBTEST(TestBind);
		}

	} ;	//! TestSocket test
};	//! Slib namespace

#endif // SOCKET_TEST_H_DEFINED
