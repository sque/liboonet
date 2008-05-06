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
			OONET_DECLARESUBTEST(TestSmartNewLineQuality, "_smart_nl() Quality");
			OONET_DECLARESUBTEST(TestSmartNewLineSpeedCRLF, "_smart_nl() \\r\\n 10k Speed");
			OONET_DECLARESUBTEST(TestSmartNewLineSpeedLF, "_smart_nl() \\n 10k Speed");
			OONET_DECLARESUBTEST(TestCtor, "ctor() default");
			OONET_DECLARESUBTEST(TestCopyCtor, "ctor() copy constructor");
			OONET_DECLARESUBTEST(TestCopyOperator, "operator= quality");
			OONET_DECLARESUBTESTEXC(TestSetHeaderWrong1, "set() wrong", "ExceptionAssertationFailed");
			OONET_DECLARESUBTEST(TestSetHeader, "set() quality");
			OONET_DECLARESUBTEST(TestSetHeaderSpeed, "set() 100k speed");
			OONET_DECLARESUBTEST(TestRemoveHeader, "erase() quality");
			OONET_DECLARESUBTEST(TestRemoveHeaderSpeed, "erase() 100k Speed");
			OONET_DECLARESUBTEST(TestRender, "render() quality");
			OONET_DECLARESUBTEST(TestRenderSpeed100k_2, "render() 100k/2H speed");
			OONET_DECLARESUBTEST(TestRenderSpeed100k_100, "render() 100k/100h speed");
			OONET_DECLARESUBTEST(TestParse, "parse() quality");
			OONET_DECLARESUBTESTEXC(TestParseWrong1, "parse() wrong", "ExceptionWrongFormat");
			OONET_DECLARESUBTEST(TestParseSpeed100k, "parse() 100k speed");
		public:
			// Constructor
			test_http_headers_list()
				:test_set("http::headers_list")
			{
				OONET_REGISTERSUBTEST(TestSmartNewLineQuality);
				OONET_REGISTERSUBTEST(TestSmartNewLineSpeedCRLF);
				OONET_REGISTERSUBTEST(TestSmartNewLineSpeedLF);
				OONET_REGISTERSUBTEST(TestCtor);
				OONET_REGISTERSUBTEST(TestCopyCtor);
				OONET_REGISTERSUBTEST(TestCopyOperator);
				OONET_REGISTERSUBTEST(TestSetHeaderWrong1);
				OONET_REGISTERSUBTEST(TestSetHeader);
				OONET_REGISTERSUBTEST(TestSetHeaderSpeed);
				OONET_REGISTERSUBTEST(TestRemoveHeader);
				OONET_REGISTERSUBTEST(TestRemoveHeaderSpeed);
				OONET_REGISTERSUBTEST(TestRender);
				OONET_REGISTERSUBTEST(TestRenderSpeed100k_2);
				OONET_REGISTERSUBTEST(TestRenderSpeed100k_100);
				OONET_REGISTERSUBTEST(TestParse);
				OONET_REGISTERSUBTEST(TestParseWrong1);
				OONET_REGISTERSUBTEST(TestParseSpeed100k);

				register_test(this);
			}

		} ;	// !test_http_headers_list class
	}	// !test namespace
};	// !oonet namespace

#endif // HTTPHEADERS_TEST_H_DEFINED
