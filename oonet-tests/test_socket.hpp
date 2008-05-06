#ifndef SOCKET_TEST_H_DEFINED
#define SOCKET_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_socket
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARESUBTEST(TestTCPCtor, "Ctor() IPv4/TCP");
			OONET_DECLARESUBTEST(TestUDPCtor, "Ctor() IPv4/UDP");

	#if OONET_OS == OONET_OS_WIN32
			OONET_DECLARESUBTEST(TestRAWCtor, "Ctor() IPv4/RAW");
	#else
			OONET_DECLARESUBTESTEXC(TestRAWCtor, "Ctor() IPv4/RAW", "ExceptionNotSupported");
	#endif


	#if OONET_OS == OONET_OS_WIN32
			OONET_DECLARESUBTESTEXC(TestWhateverCtor, "Ctor() IPv4/Invalid", "ExceptionNotSupported");
	#else
			OONET_DECLARESUBTESTEXC(TestWhateverCtor, "Ctor() IPv4/Invalid", "ExceptionWrongArgument");
	#endif
			OONET_DECLARESUBTEST(TestTCPCopyConstructor, "CopyCtor() ");
			OONET_DECLARESUBTEST(TestTCPCopyOperator, "operator=() ");
			OONET_DECLARESUBTEST(TestTCPConnect, "Connect() IPv4/TCP");
			OONET_DECLARESUBTESTEXC(TestTCPConnectWrong, "Connect() wrong", "ExceptionConnectionRefused");
			OONET_DECLARESUBTESTEXC(TestBindWrong, "Bind() wrong", "ExceptionAddressNotAvailable");
			OONET_DECLARESUBTESTEXC(TestBindRebind, "Bind() twice", "ExceptionWrongArgument");
			OONET_DECLARESUBTEST(TestBind, "Bind() normal");
			OONET_DECLARESUBTEST(TestStressConnect, "Connect() strees-test");
			OONET_DECLARESUBTEST(TestBrutalConnect, "Connect() brutal");
		public:
			// Constructor
			test_socket()
				:test_set("socket")
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

				register_test(this);
			}

		} ;	// !test_socket class
	}	// !test namespace
};	// !oonet namespace

#endif // SOCKET_TEST_H_DEFINED
