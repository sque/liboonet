#ifndef HTTPHEADERS_TEST_H_DEFINED
#define HTTPHEADERS_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_http_headers_list
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARE_SUBTEST(TestSmartNewLineQuality, "_smart_nl() Quality");
			OONET_DECLARE_SUBTEST(TestSmartNewLineSpeedCRLF, "_smart_nl() \\r\\n 10k Speed");
			OONET_DECLARE_SUBTEST(TestSmartNewLineSpeedLF, "_smart_nl() \\n 10k Speed");
			OONET_DECLARE_SUBTEST(TestCtor, "ctor() default");
			OONET_DECLARE_SUBTEST(TestCopyCtor, "ctor() copy constructor");
			OONET_DECLARE_SUBTEST(TestCopyOperator, "operator= quality");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestSetHeaderWrong1, "set() wrong", "ExceptionAssertationFailed");
			OONET_DECLARE_SUBTEST(TestSetHeader, "set() quality");
			OONET_DECLARE_SUBTEST_SPEED(TestSetHeaderSpeed, "set() 100k speed");
			OONET_DECLARE_SUBTEST(TestRemoveHeader, "erase() quality");
			OONET_DECLARE_SUBTEST(TestRemoveHeaderSpeed, "erase() 100k Speed");
			OONET_DECLARE_SUBTEST(TestRender, "render() quality");
			OONET_DECLARE_SUBTEST_SPEED(TestRenderSpeed100k_2, "render() 100k/2H speed");
			OONET_DECLARE_SUBTEST_SPEED(TestRenderSpeed100k_100, "render() 100k/100h speed");
			OONET_DECLARE_SUBTEST(TestParse, "parse() quality");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestParseWrong1, "parse() wrong", "ExceptionWrongFormat");
			OONET_DECLARE_SUBTEST_SPEED(TestParseSpeed100k, "parse() 100k speed");
		public:
			// Constructor
			test_http_headers_list()
				:test_set("http::headers_list")
			{
				OONET_EXECUTE_SUBTEST(TestSmartNewLineQuality);
				OONET_EXECUTE_SUBTEST(TestSmartNewLineSpeedCRLF);
				OONET_EXECUTE_SUBTEST(TestSmartNewLineSpeedLF);
				OONET_EXECUTE_SUBTEST(TestCtor);
				OONET_EXECUTE_SUBTEST(TestCopyCtor);
				OONET_EXECUTE_SUBTEST(TestCopyOperator);
				OONET_EXECUTE_SUBTEST(TestSetHeaderWrong1);
				OONET_EXECUTE_SUBTEST(TestSetHeader);
				OONET_EXECUTE_SUBTEST(TestSetHeaderSpeed);
				OONET_EXECUTE_SUBTEST(TestRemoveHeader);
				OONET_EXECUTE_SUBTEST(TestRemoveHeaderSpeed);
				OONET_EXECUTE_SUBTEST(TestRender);
				OONET_EXECUTE_SUBTEST(TestRenderSpeed100k_2);
				OONET_EXECUTE_SUBTEST(TestRenderSpeed100k_100);
				OONET_EXECUTE_SUBTEST(TestParse);
				OONET_EXECUTE_SUBTEST(TestParseWrong1);
				OONET_EXECUTE_SUBTEST(TestParseSpeed100k);

				register_test(this);
			}

		} ;	// !test_http_headers_list class
	}	// !test namespace
};	// !oonet namespace

#endif // HTTPHEADERS_TEST_H_DEFINED
