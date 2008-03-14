#ifndef SOCKET_TEST_H_DEFINED
#define SOCKET_TEST_H_DEFINED

#include "Test.h"

namespace OONet
{
	class TestSocket
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestTCPCtor, _T("Ctor() IPv4/TCP"));
		OONET_DECLARESUBTEST(TestUDPCtor, _T("Ctor() IPv4/UDP"));

#if OONET_OS == OONET_OS_WIN32
		OONET_DECLARESUBTEST(TestRAWCtor, _T("Ctor() IPv4/RAW"));
#else
		OONET_DECLARESUBTESTEXC(TestRAWCtor, _T("Ctor() IPv4/RAW"), _T("ExceptionNotSupported"));
#endif


#if OONET_OS == OONET_OS_WIN32
		OONET_DECLARESUBTESTEXC(TestWhateverCtor, _T("Ctor() IPv4/Invalid"), _T("ExceptionNotSupported"));
#else
        OONET_DECLARESUBTESTEXC(TestWhateverCtor, _T("Ctor() IPv4/Invalid"), _T("ExceptionWrongArgument"));
#endif
		OONET_DECLARESUBTEST(TestTCPCopyConstructor, _T("CopyCtor() "));
		OONET_DECLARESUBTEST(TestTCPCopyOperator, _T("operator=() "));
		OONET_DECLARESUBTEST(TestTCPConnect, _T("Connect() IPv4/TCP"));
		OONET_DECLARESUBTESTEXC(TestTCPConnectWrong, _T("Connect() wrong"), _T("ExceptionConnectionRefused"));
		OONET_DECLARESUBTESTEXC(TestBindWrong, _T("Bind() wrong"), _T("ExceptionAddressNotAvailable"));
		OONET_DECLARESUBTESTEXC(TestBindRebind, _T("Bind() twice"), _T("ExceptionWrongArgument"));
		OONET_DECLARESUBTEST(TestBind, _T("Bind() normal"));
		OONET_DECLARESUBTEST(TestStressConnect, _T("Connect() strees-test"));
		OONET_DECLARESUBTEST(TestBrutalConnect, _T("Connect() brutal"));
	public:
		// Constructor
		TestSocket()
			:Test(_T("Socket"))
		{
			OONET_REGISTERSUBTEST(TestTCPCtor);
			OONET_REGISTERSUBTEST(TestUDPCtor);
			OONET_REGISTERSUBTEST(TestRAWCtor);
			OONET_REGISTERSUBTEST(TestWhateverCtor);
			OONET_REGISTERSUBTEST(TestTCPCopyConstructor);
			OONET_REGISTERSUBTEST(TestTCPCopyOperator);
			OONET_REGISTERSUBTEST(TestTCPConnect);
			OONET_REGISTERSUBTEST(TestTCPConnectWrong);
			OONET_REGISTERSUBTEST(TestBindWrong);
			OONET_REGISTERSUBTEST(TestBindRebind);
			OONET_REGISTERSUBTEST(TestBind);
			OONET_REGISTERSUBTEST(TestStressConnect);
			OONET_REGISTERSUBTEST(TestBrutalConnect);
		}

	} ;	// !TestSocket class
};	// !OONet namespace

#endif // SOCKET_TEST_H_DEFINED
