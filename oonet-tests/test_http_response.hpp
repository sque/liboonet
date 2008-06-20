#ifndef HTTPRESPONSE_TEST_H_DEFINED
#define HTTPRESPONSE_TEST_H_DEFINED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_http_response
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARE_SUBTEST(TestCtor, "Ctor() default");
			OONET_DECLARE_SUBTEST(TestCopyCtor, "Ctor() copy constructor");
			OONET_DECLARE_SUBTEST(TestCopyOperator, "operator= quality");
			OONET_DECLARE_SUBTEST(TestRender, "Render() quality");
			OONET_DECLARE_SUBTEST_SPEED(TestRenderSpeed, "Render() speed 10k");
			OONET_DECLARE_SUBTEST(TestParse, "Parse() quality");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestParseWrong1, "Parse() wrong", "ExceptionWrongFormat");
			OONET_DECLARE_SUBTEST_MUSTTHROW(TestParseWrong2, "Parse() wrong", "ExceptionWrongFormat");
			OONET_DECLARE_SUBTEST_SPEED(TestParseSpeed, "Parse() speed 10k")
		public:
			// Constructor
			test_http_response()
				:test_set("http::response")
			{
				OONET_EXECUTE_SUBTEST(TestCtor);
				OONET_EXECUTE_SUBTEST(TestCopyCtor);
				OONET_EXECUTE_SUBTEST(TestCopyOperator);
				OONET_EXECUTE_SUBTEST(TestRender);
				OONET_EXECUTE_SUBTEST(TestRenderSpeed);
				OONET_EXECUTE_SUBTEST(TestParse);
				OONET_EXECUTE_SUBTEST(TestParseWrong1);
				OONET_EXECUTE_SUBTEST(TestParseWrong2);
				OONET_EXECUTE_SUBTEST(TestParseSpeed);

				register_test(this);
			}

		} ;	// !test_http_response class
	}	// !test namespace
};	// !oonet namespace

#endif // HTTPRESPONSE_TEST_H_DEFINED
