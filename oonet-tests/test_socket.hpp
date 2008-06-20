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
			OONET_DECLARE_SUBTEST(TestTCPCtor, "Ctor() IPv4/TCP");
			OONET_DECLARE_SUBTEST(TestUDPCtor, "Ctor() IPv4/UDP");

	#if (OONET_OS_API == OONET_OS_API_WIN32)
			OONET_DECLARE_SUBTEST(TestRAWCtor, "Ctor() IPv4/RAW");
	#else
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestRAWCtor, "Ctor() IPv4/RAW", "ExceptionNotSupported");
	#endif


	#if (OONET_OS_API == OONET_OS_API_WIN32)
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestWhateverCtor, "Ctor() IPv4/Invalid", "ExceptionNotSupported");
	#else
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestWhateverCtor, "Ctor() IPv4/Invalid", "ExceptionWrongArgument");
	#endif
			OONET_DECLARE_SUBTEST(TestTCPCopyConstructor, "CopyCtor() ");
			OONET_DECLARE_SUBTEST(TestTCPCopyOperator, "operator=() ");
			OONET_DECLARE_SUBTEST(TestTCPConnect, "Connect() IPv4/TCP");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestTCPConnectWrong, "Connect() wrong", "ExceptionConnectionRefused");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestBindWrong, "Bind() wrong", "ExceptionAddressNotAvailable");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestBindRebind, "Bind() twice", "ExceptionWrongArgument");
			OONET_DECLARE_SUBTEST(TestBind, "Bind() normal");
			OONET_DECLARE_SUBTEST(TestStressConnect, "Connect() strees-test");
			OONET_DECLARE_SUBTEST(TestBrutalConnect, "Connect() brutal");
		public:
			// Constructor
			test_socket()
				:test_set("socket")
			{
				OONET_EXECUTE_SUBTEST(TestTCPCtor);
				//OONET_EXECUTE_SUBTEST(TestUDPCtor);
				//OONET_EXECUTE_SUBTEST(TestRAWCtor);
				//OONET_EXECUTE_SUBTEST(TestWhateverCtor);
				OONET_EXECUTE_SUBTEST(TestTCPCopyConstructor);
				OONET_EXECUTE_SUBTEST(TestTCPCopyOperator);
				OONET_EXECUTE_SUBTEST(TestTCPConnect);
				OONET_EXECUTE_SUBTEST(TestTCPConnectWrong);
				OONET_EXECUTE_SUBTEST(TestBindWrong);
				OONET_EXECUTE_SUBTEST(TestBindRebind);
				OONET_EXECUTE_SUBTEST(TestBind);
				OONET_EXECUTE_SUBTEST(TestStressConnect);
				OONET_EXECUTE_SUBTEST(TestBrutalConnect);

				register_test(this);
			}

		} ;	// !test_socket class
	}	// !test namespace
};	// !oonet namespace

#endif // SOCKET_TEST_H_DEFINED
